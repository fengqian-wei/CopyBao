#include "typer.h"
#include <stdlib.h> // for malloc in base64.h
#include <string.h> // strlen
#include "my_config.h"
#include "util.h"
#include "io_ex.h"

GtkWidget *input_text_view;
GtkWidget *input_send_button;
GtkWidget *input_stop_button;
GtkWidget *input_reset_button;
GtkWidget *input_progress_bar;

static gchar *get_input_text()
{
    GtkTextBuffer *buffer = gtk_text_view_get_buffer(
        GTK_TEXT_VIEW(input_text_view));
    GtkTextIter begin, end;

    gtk_text_buffer_get_start_iter(buffer, &begin);
    gtk_text_buffer_get_end_iter(buffer, &end);

    return gtk_text_buffer_get_text(buffer, &begin, &end, FALSE);
}


#include "base64.h"
int current_period_index = 0;
typedef struct _SendingProcess
{
    gchar *text;
    int len;
    int i;
    gint timeout;
} SendingProcess;

SendingProcess tsp; // the sending process

static GtkWidget *btn_load_recv;
static GtkWidget *btn_encode_file;
static GtkWidget *btn_cancel_encode;
static GtkWidget *lbl_period;
static GtkWidget *btn_prev_period;
static GtkWidget *btn_next_period;

static int encode_state = 0;

static void send_enable_buttons(gboolean end)
{
    gtk_widget_set_sensitive(btn_encode_file, end);
    gtk_widget_set_sensitive(btn_cancel_encode, end);
    gtk_widget_set_sensitive(btn_load_recv, end);
    gtk_widget_set_sensitive(btn_prev_period, end);
    gtk_widget_set_sensitive(btn_next_period, end);

    if (end == TRUE) {
        if(encode_state == 0) {
            gtk_widget_set_sensitive(btn_cancel_encode, FALSE);
        } else if (encode_state == 1) {
            gtk_widget_set_sensitive(btn_encode_file, FALSE);
        }
    }
}

static void stop_sending()
{
    g_free(tsp.text);
    gtk_widget_set_sensitive(input_send_button, TRUE);
    gtk_widget_hide(input_stop_button);
    gtk_widget_set_sensitive(input_reset_button, TRUE);
    gtk_widget_set_sensitive(input_text_view, TRUE);

    send_enable_buttons(TRUE);
}

static gint do_sending(gpointer data)
{
    tsp.i++;
    gtk_progress_bar_set_fraction(
        GTK_PROGRESS_BAR(input_progress_bar),
	tsp.i * 1.0 / tsp.len
    );
    {
        char buf[16];
	sprintf(buf, "%.1f%%", tsp.i * 1.0f / tsp.len * 100);
	gtk_progress_bar_set_text(
	    GTK_PROGRESS_BAR(input_progress_bar),
	    buf);
    }

    if(tsp.i == tsp.len) {
        stop_sending();
        return FALSE;
    }
    keyboard_type(tsp.text[tsp.i]);

   return TRUE;
}

static int current_period()
{
    return the_config.period_list->periods[current_period_index];
}

static void send_button_clicked(GtkWidget *button, gpointer data)
{
    send_enable_buttons(FALSE);

    gtk_widget_set_sensitive(input_send_button, FALSE);
    gtk_widget_show(input_stop_button);
    gtk_widget_set_sensitive(input_reset_button, FALSE);
    gtk_widget_set_sensitive(input_text_view, FALSE);

    tsp.text = get_input_text();
    tsp.len = strlen(tsp.text);
    tsp.i = -1;

    tsp.timeout = g_timeout_add(current_period(), do_sending, NULL);

    puts("Start sending...");
}

static void stop_button_clicked(GtkWidget *button, gpointer data)
{
    g_source_remove(tsp.timeout);
    stop_sending();
}

static GtkTextBuffer *input_text_buffer_origin;
static GtkTextBuffer *input_text_buffer_encoded_file = NULL;

static void encode_file(GtkWidget *button, gpointer data)
{
    char *file_path = choose_file();
    if (!file_path)
        return;

    FILE *in = fopen(file_path, "rb");
    FILE *out = tmpfile();

    g_free(file_path);

    int insize = get_file_size(in);
    char buf[256];
    sprintf(buf, "%06x\n", insize);
    fputs(buf, out);

    do_base64_encode(in, out, 80);
    fclose(in);

    rewind(out);
    GtkTextBuffer *text_buffer = text_buffer_from_file(out);
    fclose(out);

    input_text_buffer_encoded_file = text_buffer;
    gtk_text_view_set_buffer(GTK_TEXT_VIEW(input_text_view), text_buffer);

    gtk_widget_set_sensitive(btn_encode_file, FALSE);
    gtk_widget_set_sensitive(btn_cancel_encode, TRUE);
    gtk_widget_set_sensitive(btn_load_recv, FALSE);
    gtk_text_view_set_editable(GTK_TEXT_VIEW(input_text_view), FALSE);
    encode_state = 1;
}

/* TODO: ? add function set_encode_state */

static void _cancel_encode()
{
    gtk_text_view_set_buffer(
        GTK_TEXT_VIEW(input_text_view), input_text_buffer_origin);
    input_text_buffer_encoded_file = NULL;

    gtk_widget_set_sensitive(btn_encode_file, TRUE);
    gtk_widget_set_sensitive(btn_cancel_encode, FALSE);
    gtk_widget_set_sensitive(btn_load_recv, TRUE);
    gtk_text_view_set_editable(GTK_TEXT_VIEW(input_text_view), TRUE);
    encode_state = 0;
}

static void cancel_encode(GtkWidget *button, gpointer data)
{
    _cancel_encode();
}

static void reset_button_clicked(GtkWidget *button, gpointer data)
{
    if (encode_state > 0)
        _cancel_encode();

    gtk_text_buffer_set_text(input_text_buffer_origin, "", -1);

    gtk_progress_bar_set_fraction(GTK_PROGRESS_BAR(input_progress_bar), 0);
    gtk_progress_bar_set_text(GTK_PROGRESS_BAR(input_progress_bar), "0.0%");
}

static void load_recv(GtkWidget *button, gpointer data)
{
    char *mem;
    int len;

    FILE *fp = fopen(the_config.recv->file, "rb");
    read_file(fp, &mem, &len);
    fclose(fp);

    gtk_text_buffer_set_text(input_text_buffer_origin, mem, len);

    g_free(mem);
}

static void load_current_period()
{
    char buf[100];
    sprintf(
        buf, "%d ms",
        the_config.period_list->periods[current_period_index]);
    gtk_label_set_text(GTK_LABEL(lbl_period), buf);
}

static void prev_period(GtkWidget *button, gpointer data)
{
    if (current_period_index > 0) {
        current_period_index--;
	load_current_period();
    }
}

static void next_period(GtkWidget *button, gpointer data)
{
    if (current_period_index < the_config.period_list->num - 1) {
        current_period_index++;
	load_current_period();
    }
}

GtkWidget *create_input_window()
{
    GtkWidget *window;
    GtkWidget *vbox;
    GtkWidget *hbox1, *hbox2, *hbox3;
    GtkWidget *label, *label2;
    GtkWidget *scrollwin;
    GtkWidget *text_view;
    GtkWidget *button, *button2, *button3;
    GtkWidget *progress_bar;

    /* window */
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Typer");
    gtk_window_set_default_size(GTK_WINDOW(window), 800, 400);
    // gtk_window_set_deletable(GTK_WINDOW(window), FALSE);
    gtk_window_set_type_hint(GTK_WINDOW(window), GDK_WINDOW_TYPE_HINT_DIALOG);
    gtk_container_border_width(GTK_CONTAINER(window), 10);
    g_signal_connect(
        GTK_OBJECT(window), "delete_event",
        GTK_SIGNAL_FUNC(gtk_widget_hide_on_delete), NULL);

    vbox = gtk_vbox_new(FALSE, 10);

    /* encoding & recv */
    GtkWidget *hbox4 = gtk_hbox_new(FALSE, 10);
    btn_load_recv = gtk_button_new_with_label("Load Recv");
    if (!the_config.recv->file)
        gtk_widget_set_sensitive(btn_load_recv, FALSE);
    g_signal_connect (
        GTK_OBJECT(btn_load_recv), "clicked",
        GTK_SIGNAL_FUNC(load_recv), NULL);
    gtk_box_pack_end (GTK_BOX(hbox4), btn_load_recv, FALSE, FALSE, 0);
    btn_encode_file = gtk_button_new_with_label("Encode File");
    g_signal_connect (
        GTK_OBJECT(btn_encode_file), "clicked",
        GTK_SIGNAL_FUNC(encode_file), NULL);
    gtk_box_pack_start (GTK_BOX(hbox4), btn_encode_file, FALSE, FALSE, 0);
    btn_cancel_encode = gtk_button_new_with_label("Cancel Encode");
    gtk_widget_set_sensitive(btn_cancel_encode, FALSE);
    g_signal_connect(
        GTK_OBJECT(btn_cancel_encode), "clicked",
        GTK_SIGNAL_FUNC(cancel_encode), NULL);
    gtk_box_pack_start (GTK_BOX(hbox4), btn_cancel_encode, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), hbox4, FALSE, FALSE, 0);

    hbox1 = gtk_hbox_new(FALSE, 10);
    label = gtk_label_new("Text:");
    gtk_box_pack_start(GTK_BOX(hbox1), label, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), hbox1,
                       FALSE, FALSE, 0);

    /* center text view */
    text_view = gtk_text_view_new();
    gtk_text_view_set_wrap_mode(GTK_TEXT_VIEW(text_view), GTK_WRAP_CHAR);
    input_text_buffer_origin =
        gtk_text_view_get_buffer(GTK_TEXT_VIEW(text_view));
    g_object_ref(input_text_buffer_origin);
    scrollwin = gtk_scrolled_window_new(
      NULL,
      gtk_text_view_get_vadjustment(GTK_TEXT_VIEW(text_view)));
    gtk_scrolled_window_set_policy(
        GTK_SCROLLED_WINDOW(scrollwin),
        GTK_POLICY_NEVER,
        GTK_POLICY_ALWAYS);
    gtk_scrolled_window_set_shadow_type(
        GTK_SCROLLED_WINDOW(scrollwin),
        GTK_SHADOW_IN);
    gtk_container_add(GTK_CONTAINER(scrollwin), text_view);
    gtk_box_pack_start(GTK_BOX(vbox), scrollwin,
                       TRUE, TRUE, 0);

    /* progress bar */
    label2 = gtk_label_new("Progress: ");
    progress_bar = gtk_progress_bar_new();
    hbox3 = gtk_hbox_new(FALSE, 10);
    gtk_box_pack_start(GTK_BOX(hbox3), label2, FALSE, FALSE, 0);
    gtk_box_pack_start(
        GTK_BOX(hbox3), progress_bar,
        FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), hbox3, FALSE, FALSE, 0);

    /* period setting */
    GtkWidget *hbox5 = gtk_hbox_new(FALSE, 10);
    gtk_box_pack_start(
        GTK_BOX(hbox5), gtk_label_new("Period: "),
	FALSE, FALSE, 0);
    btn_prev_period = gtk_button_new_with_label("<<");
    g_signal_connect(
        GTK_OBJECT(btn_prev_period), "clicked",
	GTK_SIGNAL_FUNC(prev_period), NULL);
    gtk_box_pack_start(GTK_BOX(hbox5), btn_prev_period, FALSE, FALSE, 0);
    lbl_period = gtk_label_new(NULL);
    load_current_period();
    gtk_box_pack_start(GTK_BOX(hbox5), lbl_period, FALSE, FALSE, 0);
    btn_next_period = gtk_button_new_with_label(">>");
    g_signal_connect(
        GTK_OBJECT(btn_next_period), "clicked",
	GTK_SIGNAL_FUNC(next_period), NULL);
    gtk_box_pack_start(GTK_BOX(hbox5), btn_next_period, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), hbox5, FALSE, FALSE, 0);

    /* buttons on the BOTTOM */
    hbox2 = gtk_hbox_new(FALSE, 10);
    button = gtk_button_new_with_label("Send");
    gtk_widget_set_size_request(button, 100, 40);
    g_signal_connect(
        GTK_OBJECT(button), "clicked",
        GTK_SIGNAL_FUNC(send_button_clicked), NULL);
    gtk_box_pack_end(GTK_BOX(hbox2), button, FALSE, FALSE, 0);
    button2 = gtk_button_new_with_label("STOP!");
    gtk_widget_set_size_request(button2, 100, 40);
    g_signal_connect(
        GTK_OBJECT(button2), "clicked",
        GTK_SIGNAL_FUNC(stop_button_clicked), NULL);
    gtk_box_pack_end(GTK_BOX(hbox2), button2, FALSE, FALSE, 0);
    button3 = gtk_button_new_with_label("Reset");
    gtk_widget_set_size_request(button3, 100, 40);
    g_signal_connect(
        GTK_OBJECT(button3), "clicked",
        GTK_SIGNAL_FUNC(reset_button_clicked), NULL);
    gtk_box_pack_start(GTK_BOX(hbox2), button3, FALSE, FALSE, 0);

    gtk_box_pack_start(GTK_BOX(vbox), hbox2, FALSE, FALSE, 0);

    gtk_container_add(GTK_CONTAINER(window), vbox);

    input_send_button = button;
    input_stop_button = button2;
    input_reset_button = button3;
    input_text_view = text_view;
    input_progress_bar = progress_bar;

    gtk_widget_show_all(window);
    gtk_widget_hide(button2);

    return window;
}



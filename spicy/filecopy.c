#include <stdio.h>
#include <gtk/gtk.h>
#include <spice-client.h>
#include "util.h"

static SpiceMainChannel *channel;
static GtkWindow *window;
static GtkProgressBar *progress_bar; 
static GCancellable *canceller;
static GFile *files[2] = { NULL, NULL };

static void end_copy();

static void cb_progress(goffset sent, goffset total, gpointer data)
{
    g_message("FileSender.progress");

    gtk_progress_bar_set_fraction(progress_bar, (gdouble) sent / total);

    char buf[100];
    sprintf(buf, "%.1lfkB / %.1lfkB", sent / 1024.0, total / 1024.0);
    gtk_progress_bar_set_text(progress_bar, buf);
}

static void cb_finish(GObject *source, GAsyncResult *res, gpointer user_data)
{
    g_message("FileSender.finish");

    gboolean success = spice_main_file_copy_finish(channel, res, NULL);
    if (success) {
        msgbox("Copy successfully.");
    }
    else {
        if (!g_cancellable_is_cancelled(canceller))
            msgbox("Fail! Try again.");
    }
    end_copy();
}

static void cb_abort(GtkWidget *button, gpointer data)
{
    g_cancellable_cancel(canceller);
}

static void init_window(const char *from, const char *to)
{
    char buf[200];
    GtkBox *vbox;
    GtkBox *hbox1;
    GtkLabel *lb_from, *lb_to;
    GtkButton *btn_abort;

    window = GTK_WINDOW(gtk_window_new(GTK_WINDOW_TOPLEVEL));
    gtk_window_set_title(window, "Copy File");
    gtk_container_border_width(GTK_CONTAINER(window), 10);
    gtk_window_set_type_hint(window, GDK_WINDOW_TYPE_HINT_DIALOG);
    gtk_window_set_deletable(window, FALSE);
    gtk_window_set_modal(window, TRUE);

    vbox = GTK_BOX(gtk_vbox_new(FALSE, 10));

    sprintf(buf, "From: %s", from);
    lb_from = GTK_LABEL(gtk_label_new(buf));
    gtk_box_pack_start(vbox, GTK_WIDGET(lb_from), FALSE, FALSE, 0);

    sprintf(buf, "To: %s", to);
    lb_to = GTK_LABEL(gtk_label_new(buf));
    gtk_box_pack_start(vbox, GTK_WIDGET(lb_to), FALSE, FALSE, 0);

    hbox1 = GTK_BOX(gtk_hbox_new(FALSE, 10));
    {
        GtkLabel *lb_progress = GTK_LABEL(gtk_label_new("Progress:"));
	gtk_box_pack_start(hbox1, GTK_WIDGET(lb_progress), FALSE, FALSE, 0);
    }
    progress_bar = GTK_PROGRESS_BAR(gtk_progress_bar_new());
    gtk_box_pack_start(hbox1, GTK_WIDGET(progress_bar), TRUE, TRUE, 0);
    gtk_box_pack_start(vbox, GTK_WIDGET(hbox1), FALSE, FALSE, 0);

    btn_abort = GTK_BUTTON(gtk_button_new_with_label("Abort!"));
    g_signal_connect(
        GTK_OBJECT(btn_abort), "clicked",
	GTK_SIGNAL_FUNC(cb_abort), NULL);
    gtk_box_pack_start(vbox, GTK_WIDGET(btn_abort), FALSE, FALSE, 0);

    gtk_container_add(GTK_CONTAINER(window), GTK_WIDGET(vbox));
    gtk_widget_show_all(GTK_WIDGET(window));
}

static void close_window()
{
    gtk_widget_destroy(GTK_WIDGET(window));
}

void filecopy_init(SpiceChannel *main_channel)
{
    channel = SPICE_MAIN_CHANNEL(main_channel);
}

static void begin_copy(const char *path_utf8)
{
    files[0] = g_file_new_for_path(path_utf8);
    canceller = g_cancellable_new();

    spice_main_file_copy_async(channel, files,
        G_FILE_COPY_OVERWRITE, canceller, 
        cb_progress, NULL, cb_finish, NULL);

    char buf_to[200];
    gchar *fn = g_path_get_basename(path_utf8);
    sprintf(buf_to, "C:\\Documents and Settings\\cls\\%s", fn);
    g_free(fn);
    init_window(path_utf8, buf_to);
}

static void end_copy()
{ 
    close_window();
    g_object_unref(files[0]);
    g_object_unref(canceller);
}

static gchar *my_choose_file();

void filecopy()
{
    gchar *path = my_choose_file();
    if (path == NULL)
        return;

    begin_copy(path);
    g_free(path);
}

static gchar *my_choose_file()
{
    GtkWidget *dialog = gtk_file_chooser_dialog_new(
        "Choose File to Copy", NULL,
	GTK_FILE_CHOOSER_ACTION_OPEN,
	GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL,
	GTK_STOCK_OPEN, GTK_RESPONSE_ACCEPT,
	NULL);
    gchar *path = NULL;

    if (gtk_dialog_run(GTK_DIALOG(dialog)) == GTK_RESPONSE_ACCEPT) {
	path = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialog));
    }

    gtk_widget_destroy(dialog);

    return path;
}



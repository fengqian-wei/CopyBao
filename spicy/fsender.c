#include "fsender.h"
#include "dtp.h"
#include <stdio.h>
#include <string.h>
#include <gtk/gtk.h>
#include "util.h"

#define BLKSIZE 512

static FILE *fp = NULL;
static int nbytes_remain;
static int nblk_sent, nblk_total;
static gchar *filename;
static GtkWindow *window;
static GtkLabel *lb_message, *lb_progress, *lb_status;

static GtkWindow *create_window();
static void do_sending(void *);

static void update_status(int state, int sent, int total)
{
    char buf[200];
    switch (state) {
    case 0:
        strcpy(buf, "NOT-START");
	break;
    case 1:
        strcpy(buf, "INIT");
	break;
    case 2:
        sprintf(buf, "SEND %d / %d", sent, total);
	break;
    case 3:
        strcpy(buf, "FINI");
	break;
    }
    gtk_label_set_text(lb_status, buf);
}

static void start_sending()
{
    window = create_window();

    dtp_state_update = update_status;

    char buf[200];
    char *filename_base64 = g_base64_encode((guchar *) filename, strlen(filename));
    sprintf(buf, "f%s|%d", filename_base64, nbytes_remain);
    g_free(filename_base64);

    dtp_transfer(buf, do_sending, NULL);
}

static void end_sending()
{
    fclose(fp);

    dtp_stop();

    dtp_state_update = NULL;

    gtk_widget_destroy(GTK_WIDGET(window));
}

static void abort_sending()
{
    end_sending();
}

static void transfer_ended(void *unused)
{
    end_sending();
}

static void do_sending(void *unused)
{
    static char outbuf[(BLKSIZE + 2) / 3 * 4 + 2];
    static char inbuf[BLKSIZE];
    int nbytes_read;

    nbytes_read = fread(inbuf, 1, BLKSIZE, fp);
    nbytes_remain -= nbytes_read;
    nblk_sent++;

    {
        char buf[100];
	sprintf(buf, "%d / %d", nblk_sent, nblk_total);
	gtk_label_set_text(lb_progress, buf);
    }

    char *blk_base64 = g_base64_encode((guchar *) inbuf, nbytes_read);
    sprintf(outbuf, "d%s", blk_base64);
    g_free(blk_base64);

    if (nbytes_remain > 0) 
        dtp_transfer(outbuf, do_sending, NULL);
    else
        dtp_transfer(outbuf, transfer_ended, NULL);
}

static void cb_abort(GtkWidget *button, gpointer data)
{
    abort_sending();
}

static GtkWindow *create_window()
{
    GtkWindow *window;
    GtkBox *vbox;
    GtkButton *btn_abort;
    GtkAlignment *align;
    char buf[256];

    window = GTK_WINDOW(gtk_window_new(GTK_WINDOW_TOPLEVEL));
    gtk_window_set_title(window, "File Sender");

    /* padding */
    gtk_container_border_width(GTK_CONTAINER(window), 10);

    /* hide max/min button */
    gtk_window_set_type_hint(window, GDK_WINDOW_TYPE_HINT_DIALOG);

    /* disable close button */
    gtk_window_set_deletable(window, FALSE);

    /* modal */
    gtk_window_set_modal(window, TRUE);

    vbox = GTK_BOX(gtk_vbox_new(FALSE, 10));

    sprintf(buf, "Sending file %s...", filename);
    lb_message = GTK_LABEL(gtk_label_new(buf));
    gtk_box_pack_start(vbox, GTK_WIDGET(lb_message), FALSE, FALSE, 0);

    lb_progress = GTK_LABEL(gtk_label_new("0 / 0"));
    gtk_box_pack_start(vbox, GTK_WIDGET(lb_progress), FALSE, FALSE, 0);

    lb_status = GTK_LABEL(gtk_label_new("INIT"));
    gtk_box_pack_start(vbox, GTK_WIDGET(lb_status), FALSE, FALSE, 0);

    btn_abort = GTK_BUTTON(gtk_button_new_with_label("Abort!"));
    gtk_widget_set_size_request(GTK_WIDGET(btn_abort), 100, 40);
    g_signal_connect(
        GTK_OBJECT(btn_abort), "clicked",
	GTK_SIGNAL_FUNC(cb_abort), NULL);

    align = GTK_ALIGNMENT(gtk_alignment_new(0.5, 0.5, 0, 0));
    gtk_container_add(GTK_CONTAINER(align), GTK_WIDGET(btn_abort));
    gtk_box_pack_start(vbox, GTK_WIDGET(align), FALSE, FALSE, 0);

    gtk_container_add(GTK_CONTAINER(window), GTK_WIDGET(vbox));
    gtk_widget_show_all(GTK_WIDGET(window));

    return window;
}

char *my_choose_file();

void fsender()
{
    gchar *path_utf8 = my_choose_file();
    if (path_utf8 == NULL)
        return;

    filename = g_path_get_basename(path_utf8);
    gchar *path_local = g_locale_from_utf8(path_utf8, -1, NULL, NULL, NULL);

    fp = fopen(path_local, "rb");
    g_free(path_local);
    if (!fp) {
        msgbox("Can't open file!");
	goto bad;
    }
    
    int nb = get_file_size(fp);
    if (nb > 512 * 1024) {
        msgbox("File is too big! (> 500kB)");
	goto bad2;
    }

    nbytes_remain = nb;
    nblk_sent = 0;
    nblk_total = (nb + BLKSIZE - 1) / BLKSIZE;

    start_sending();

    return;

bad2:
    fclose(fp);
bad:
    g_free(filename);
}

gchar *my_choose_file()
{
    GtkWidget *dialog = gtk_file_chooser_dialog_new(
        "Choose File to Transfer", NULL,
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



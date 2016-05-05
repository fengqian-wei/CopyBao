#include "util.h"
#include <sys/stat.h>

long get_file_size(FILE *fp)
{
    int fd = fileno(fp);
    struct stat st;
    fstat(fd, &st);
    return st.st_size;
}

void read_file(FILE *fp, char **mem_ptr, int *len_ptr)
{
    int len = get_file_size(fp);
    char *mem = (char *) g_malloc(len);
    fread(mem, 1, len, fp);

    *mem_ptr = mem;
    *len_ptr = len;
}

GtkTextBuffer *text_buffer_from_file(FILE *fp)
{
    char *mem;
    int len;
    read_file(fp, &mem, &len);

    GtkTextBuffer *text_buffer = gtk_text_buffer_new(NULL);
    /* FIXME: mem can be non-UTF8, which is not allowed here */
    gtk_text_buffer_set_text(text_buffer, mem, len);

    g_free(mem);

    return text_buffer;
}

char *choose_file()
{
    GtkWidget *dialog = gtk_file_chooser_dialog_new(
        "Choose...", NULL,
	GTK_FILE_CHOOSER_ACTION_OPEN,
	GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL,
	GTK_STOCK_OPEN, GTK_RESPONSE_ACCEPT,
	NULL);
    char *path = NULL;

    if (gtk_dialog_run(GTK_DIALOG(dialog)) == GTK_RESPONSE_ACCEPT) {
	char *orig_path = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialog));
        path = g_locale_from_utf8(orig_path, -1, NULL, NULL, NULL);
        g_free(orig_path);
    }

    gtk_widget_destroy(dialog);

    return path;
}

void msgbox(char *m)
{
    GtkWidget *dialog = gtk_message_dialog_new(
        GTK_WINDOW(NULL), GTK_DIALOG_MODAL, GTK_MESSAGE_INFO,
	GTK_BUTTONS_OK, m);
    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);
}



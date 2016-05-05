#include "my_config.h"
#include <gtk/gtk.h>

static gint default_periods[] = { 1, 2, 5, 10, 20, 50, 100, 200, 500 };

static PeriodList default_period_list =
{
    default_periods,
    sizeof(default_periods) / sizeof(gint)
};

static PeriodList user_period_list;

static Recv default_recv =
{
    NULL,
    0
};

static Recv user_recv;

Config the_config = { &default_period_list, &default_recv };

static int find_period(PeriodList *period_list, int desired, int default_value)
{
    int i;

    for (i = 0; i < period_list->num; i++)
        if (period_list->periods[i] == desired)
            return i;

    return default_value;
}

void load_config()
{
    GKeyFile *config = g_key_file_new();

    if (g_key_file_load_from_file (
        config, "config.txt", G_KEY_FILE_NONE, NULL) == FALSE)
    {
        GtkWidget *dialog = gtk_message_dialog_new(
            NULL, GTK_DIALOG_MODAL, GTK_MESSAGE_WARNING,
            GTK_BUTTONS_OK, "can't load config.txt.");
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
    }
    else {
	user_period_list.periods = g_key_file_get_integer_list (
            config, "main", "periods", &user_period_list.num, NULL);
	if (user_period_list.periods && user_period_list.num > 0)
            the_config.period_list = &user_period_list;

        extern int current_period_index;
        int default_period = g_key_file_get_integer(
            config, "main", "default_period", NULL);
        if (default_period > 0)
            current_period_index = find_period(
                the_config.period_list, default_period, 0);

        user_recv.file = g_key_file_get_string (
	    config, "recv", "file", NULL);
	if (user_recv.file) {
            gint recv_period = g_key_file_get_integer (
	        config, "recv", "period", NULL);
	    int i;

            user_recv.period_index = find_period(the_config.period_list, recv_period, -1);

            the_config.recv = &user_recv;
	}
    }

    g_key_file_free(config);
}

void unload_config()
{
    if (the_config.period_list == &user_period_list) {
        g_free (user_period_list.periods);
    }
    if (the_config.recv == &user_recv) {
        g_free (user_recv.file);
    }
}



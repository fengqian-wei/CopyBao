#ifndef __UTIL_H__
#define __UTIL_H__

#include <stdio.h>
#include <gtk/gtk.h>

long get_file_size(FILE *fp);
void read_file(FILE *fp, char **mem_ptr, int *len_ptr);
GtkTextBuffer *text_buffer_from_file(FILE *fp);
char *choose_file();
void msgbox(char *m);

#endif


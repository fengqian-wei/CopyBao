#ifndef __IO_EX_H__
#define __IO_EX_H__

#include <glib.h>
#include <spice-client.h>

void keyboard_init(SpiceChannel *channel);
void keyboard_type(gchar c);

enum SpiceSurfaceFmt d_format;
gint                 d_width, d_height, d_stride;
gpointer             d_data;

void display_init(SpiceChannel *channel);
uint32_t display_get_pixel(int x, int y);
void display_invalidate_add_handler(void (*handler)());

#endif


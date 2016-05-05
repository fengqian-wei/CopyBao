#ifndef __IO_EX_H__
#define __IO_EX_H__

/* includes! */

void keyboard_init(SpiceChannel *channel);
void keyboard_type(gchar c);

void display_init(SpiceChannel *channel);
uint32_t display_get_pixel(int x, int y);
void display_invalidate_add_handler(void (*handler)());

#endif


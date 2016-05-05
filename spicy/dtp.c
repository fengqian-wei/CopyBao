#include <stdio.h>
#include <string.h>

static char buffer[4096];
static int length, sent;
static int state = 0;
static gint timeout;
static void (*g_callback)(void *);
static void *g_user_data;

static int saved_status = 1, saved_result = 0;

void (*dtp_state_update)(int state, int sent, int total) = NULL;

#define PERIOD 10

#define BLACK 0x000000
#define RED 0xFF0000
#define GREEN 0x008000

static void broadcast_state_update(int sent, int total)
{
    if (dtp_state_update != NULL)
        dtp_state_update(state, sent, total);
}

static void switch_state(int new_state)
{
    state = new_state;
    broadcast_state_update(state, 0, 0);
}

static void enter_sending()
{
    gint do_sending(gpointer);

    switch_state(2);
    timeout = g_timeout_add(PERIOD, do_sending, NULL);
}

static void leave_sending()
{
    g_source_remove(timeout);
    switch_state(3);
}

static gint do_sending(gpointer data)
{
    keyboard_type(buffer[sent]);
    if (++sent == length) {
        leave_sending();
	return FALSE;
    }
   
    broadcast_state_update(2, sent, length);
    return TRUE;
}

static void on_status_change()
{
    uint32_t color_ul = 0; // up left
    uint32_t color_ur = 0; // up right

    int status = -1, result = -1;

    if (color_ul == BLACK)
        status = 0;
    else if (color_ul == RED)
        status = 1;

    if (color_ur == BLACK)
        result = 0;
    else if (color_ur == RED)
        result = 1;
    else if (color_ur == GREEN)
        result = 2;

    if (status < 0 || result < 0)
        return;

    saved_status = status;
    saved_result = result;

    if (state == 1) {
        if (status == 0) {
	    enter_sending();
	}
    }
    else if (state == 2) {
        if (status == 1 && result == 1) {
	    leave_sending();
	}
    }
    else if (state == 3) {
        if (status == 0) {
	    if (result == 2) {
	        g_callback(g_user_data);
		switch_state(0);
	    }
	    else {
                switch_state(1);
	    }
	}
    }
}

void dtp_init()
{
    display_invalidate_add_handler(on_status_change);
}

unsigned csharp_hashcode(const char *s);

void dtp_transfer(char *str, void (*callback)(void *), void *user_data)
{
    unsigned hash = (csharp_hashcode(str) >> 4) & 0xFFFF;
    
    sprintf(buffer, "<%04X%s>", hash, str);
    length = strlen(buffer);

    g_callback = callback;
    g_user_data = user_data;

    if (saved_status == 0) {
        switch_state(1);
    }
    else {
        enter_sending();
    }
}


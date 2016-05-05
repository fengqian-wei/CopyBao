
enum SpiceSurfaceFmt d_format;
gint                 d_width, d_height, d_stride;
gpointer             d_data;

static void cb_primary_create(SpiceChannel *channel, gint format,
                              gint width, gint height, gint stride,
                              gint shmid, gpointer imgdata, gpointer data)
{
    d_format = format;
    d_width  = width;
    d_height = height;
    d_stride = stride;
    d_data   = imgdata;
}

static void cb_invalidate(SpiceChannel *channel,
                          gint x, gint y, gint w, gint h, gpointer *data)
{
    void (*handler)() = data;
    handler();
#if 0
    g_message("invalidate: %d %d %d", d_width, d_height, d_stride);

    uint8_t r, g, b;
    uint8_t *p;

    p = d_data;
    r = p[2];
    g = p[1];
    b = p[0];

    g_message("UL: #%02x%02x%02x", r, g, b);

    p = d_data + d_width * 4 - 4;
    r = p[2];
    g = p[1];
    b = p[0];

    g_message("UR: #%02x%02x%02x", r, g, b);
#endif
}

void display_init(SpiceChannel *channel)
{
    g_signal_connect(channel, "display-primary-create",
                     G_CALLBACK(cb_primary_create), NULL);
}

uint32_t display_get_pixel(int x, int y)
{
    uint8_t p = d_data + d_stride * y + x * 4;
    
    return *(uint32_t *)p;
}

void display_invalidate_add_handler(void (*handler)())
{
    g_signal_connect(channel, "display-invalidate",
                     G_CALLBACK(cb_invalidate), handler);
}


#include "io_ex.h"
#include "finger.h"

#define P(c)  spice_inputs_key_press(inputs_channel, c)
#define R(c)  spice_inputs_key_release(inputs_channel, c)
#define PR(c) spice_inputs_key_press_and_release(inputs_channel, c)
#define LSHIFT 0x2A
#define PR_S(c) do { P(LSHIFT); PR(c); R(LSHIFT); } while(0)

static SpiceInputsChannel *inputs_channel;

void keyboard_init(SpiceChannel *channel)
{
    inputs_channel = SPICE_INPUTS_CHANNEL(channel);
}

void keyboard_type(gchar c)
{
    Finger *pf = &char_map[(guchar) c];
    if (pf->code == 0)
        return;

    if (pf->shift)
        PR_S(pf->code);
    else
        PR(pf->code);
}


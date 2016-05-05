#ifndef __DTP_H__
#define __DTP_H__

extern void dtp_init();
extern void dtp_transfer(char *str, void (*callback)(void *), void *user_data);
extern void (*dtp_state_update)(int state, int sent, int total);

#endif


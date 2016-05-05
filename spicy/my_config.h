#ifndef __MY_CONFIG_H__
#define __MY_CONFIG_H__

#include <glib.h>

typedef struct _PeriodList
{
    gint *periods;
    gsize num;
} PeriodList;

typedef struct _Recv
{
    char *file;
    int period_index;
} Recv;

typedef struct _Config
{
    PeriodList *period_list;
    Recv *recv;
} Config;

extern Config the_config;
extern void load_config();
extern void unload_config();

#endif

#ifndef _marmite_term
#define _marmite_term 1

#include <glib-object.h>
#include "config.h"
typedef struct MarmiteHooks {
    void * data;
    void (*set_title)(void *, const char *);
    void (*all_done)(void *);
} MarmiteHooks;

GObject *marmite_vte(MarmiteConfig *cfg, MarmiteHooks *hooks);

#endif

#ifndef _marmite_config
#define _marmite_config 1

typedef struct MarmiteConfig {
    char *title;
    char *font;
    char **command;
    int scrollback;
} MarmiteConfig;

MarmiteConfig *marmite_config(int argc, char *argv[], GOptionGroup *extra_options);

#endif

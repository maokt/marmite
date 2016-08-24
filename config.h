#ifndef _marmite_config
#define _marmite_config 1

typedef struct MarmiteConfig {
    char *font;
    char **command;
} MarmiteConfig;

MarmiteConfig *marmite_config(int argc, char *argv[], GOptionGroup *extra_options);

#endif

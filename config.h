typedef struct MarmiteConfig {
    char *font;
    char **command;
} MarmiteConfig;

MarmiteConfig *marmite_config(int argc, char *argv[], GOptionGroup *extra_options);

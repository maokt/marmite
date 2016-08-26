#define MAYBE_POSIX_C_SOURCE 200809L
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>
#include <glib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "config.h"

static MarmiteConfig cfg;

static GOptionEntry entries[] = {
	{ "title", 't', 0, G_OPTION_ARG_STRING, &cfg.title, "Set window title", "\"title\"" },
	{ "font", 'f', 0, G_OPTION_ARG_STRING, &cfg.font, "Select terminal font", "\"font name\"" },
	{ "scrollback", 's', 0, G_OPTION_ARG_INT, &cfg.scrollback, "Size of scrollback buffer", "\"lines\"" },
	{ "light", 'l', 0, G_OPTION_ARG_NONE, &cfg.colour_mode, "Enable light colour mode", NULL },
	{ G_OPTION_REMAINING, 0, 0, G_OPTION_ARG_STRING_ARRAY, &cfg.command, "command to run", "[command]" },
	{ NULL }
};

static char **get_default_command() {
    static char *command[2] = { NULL, NULL };
    static char buffer[64];

    command[0] = getenv("SHELL");

    if (!command[0]) {
        struct passwd *user = getpwuid(getuid());
        if (user && user->pw_shell && strlen(user->pw_shell) < sizeof buffer) {
            strcpy(buffer, user->pw_shell);
            command[0] = buffer;
        }
    }

    if (!command[0]) command[0] = "/bin/sh";

    return command;
}

MarmiteConfig *marmite_config(int argc, char *argv[], GOptionGroup *extra_options) {
    // set defaults
    cfg.title = "Marmite";
    cfg.font = "M+ 1mn regular,VL Gothic,Noto Sans Mono CJK JP 16";
    cfg.command = NULL;
    cfg.scrollback = 0;
    cfg.colour_mode = 0;

    GOptionContext *context = g_option_context_new("- Mini Terminal Emulator");
    g_option_context_set_summary(context, "Version 0.1;");
	g_option_context_add_main_entries(context, entries, NULL);
	if (extra_options) g_option_context_add_group(context, extra_options);

#if GLIB_CHECK_VERSION(2,44,0)
    g_option_context_set_strict_posix(context, TRUE);
#endif

    gboolean ok = g_option_context_parse(context, &argc, &argv, NULL);
    g_option_context_free(context);
    if (!ok) return NULL;

    if (!cfg.command) {
        cfg.command = get_default_command();
        if (!cfg.scrollback) cfg.scrollback = 200;
    }

    return &cfg;
}

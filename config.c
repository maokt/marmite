#define MAYBE_POSIX_C_SOURCE 200809L
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>
#include <glib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "config.h"

static MarmiteConfig cfg = {
    .font = "VL Gothic 16"
};

static GOptionEntry entries[] = {
	{ "font", 'f', 0, G_OPTION_ARG_STRING, &cfg.font, "Select terminal font", "\"font name\"" },
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
    GOptionContext *context = g_option_context_new("- Mini Terminal Emulator");
    g_option_context_set_summary(context, "Version 0.1;");
	g_option_context_add_main_entries(context, entries, NULL);
	if (extra_options) g_option_context_add_group(context, extra_options);

#if GLIB_CHECK_VERSION(2,44,0)
    g_option_context_set_strict_posix(context, TRUE);
#endif

    // hack to handle the first -e for compatiblity with some other terminals
    for (char **p = argv; *p; ++p) {
        if (strcmp(*p, "-e") == 0) (*p)[1] = '-';
        if (strcmp(*p, "--") == 0) break;
    }

    gboolean ok = g_option_context_parse(context, &argc, &argv, NULL);
    g_option_context_free(context);
    if (!ok) return NULL;

    if (!cfg.command) cfg.command = get_default_command();

    return &cfg;
}

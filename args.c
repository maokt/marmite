#include <glib.h>
#include <locale.h>
#include <stdio.h>

static const char *o_font = "default font";
static gchar **o_args = NULL;
static gboolean o_exec = FALSE;
static gboolean o_version = FALSE;
static gint o_number = 99;

static GOptionEntry entries[] = {
	{ "version", 'v', 0, G_OPTION_ARG_NONE, &o_version, "Print version number", NULL },
	{ "font", 'f', 0, G_OPTION_ARG_STRING, &o_font, "Select initial terminal font", NULL },
	{ "number", 'n', 0, G_OPTION_ARG_INT, &o_number, "Select initial number of tabs", NULL },
	{ G_OPTION_REMAINING, 0, 0, G_OPTION_ARG_STRING_ARRAY, &o_args, NULL, NULL },
	{ "execute", 'e', 0, G_OPTION_ARG_NONE, &o_exec, "Execute command (last option in the command line)", NULL },
	{ NULL }
};

static gchar *cmd_shell[] = { "bash", NULL };

void marmite_args(int argc, char *argv[], GOptionGroup *extra_options) {
    GOptionContext *context;

	setlocale(LC_ALL, "");

    o_args = cmd_shell;

	context = g_option_context_new("- mini terminal emulator");
	g_option_context_add_main_entries(context, entries, NULL);
	if (extra_options) g_option_context_add_group(context, extra_options);
	// g_option_group_set_translation_domain(gtk_get_option_group(TRUE), GETTEXT_PACKAGE);
#if GLIB_CHECK_VERSION(2,44,0)
    g_option_context_set_strict_posix(context, TRUE);
#endif
    for (char **p = argv; *p; ++p)
        if ((*p)[0] == '-' && (*p)[1] == 'e')
            (*p)[1] = '-';
    g_option_context_parse(context, &argc, &argv, NULL);

    printf("number=%d; version=%d; exec=%d;\n", o_number, o_version, o_exec);
    printf("font=%s;\n", o_font);
    printf("args=[");
    for (gchar **p = o_args; *p; ++p)
        printf("\"%s\",", *p);
    printf("]\n");
}

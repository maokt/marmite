#include <glib.h>
#include <locale.h>
#include "config.h"

static MarmiteConfig *run_opts(int argc, ...) {
    char *argv[argc+1];
    va_list varg;
    va_start(varg, argc);
    for (int n = 0; n < argc; ++n) {
        argv[n] = va_arg(varg, char*);
    }
    va_end(varg);
    argv[argc] = NULL;
    return marmite_config(argc, argv, NULL);
}

static void default_config(void) {
    MarmiteConfig *cfg = run_opts(1, "marmite");
    g_assert_nonnull(cfg);
    g_assert_true(g_str_has_suffix(cfg->command[0], "sh"));
    g_assert_cmpstr(cfg->font, ==, "VL Gothic 16");
}

static void opt_font(void) {
    const char *fontname = "Another Font";
    MarmiteConfig *cfg = run_opts(3, "marmite", "-f", fontname);
    g_assert_nonnull(cfg);
    g_assert_cmpstr(cfg->font, ==, fontname);
}

static void opt_command(void) {
    char *argv[] = { "marmite", "foo", "-e", "bar", NULL };
    MarmiteConfig *cfg = marmite_config(4, argv, NULL);
    g_assert_nonnull(cfg);
    g_assert_cmpstr(cfg->command[0], ==, "foo");
    g_assert_cmpstr(cfg->command[1], ==, "-e");
    g_assert_cmpstr(cfg->command[2], ==, "bar");
    g_assert_null(cfg->command[3]);
}

int main (int argc, char *argv[]) {
    setlocale (LC_ALL, "");
    g_test_init(&argc, &argv, NULL);
    g_test_add_func("/marmite/config/default", default_config);
    g_test_add_func("/marmite/config/font", opt_font);
    g_test_add_func("/marmite/config/command", opt_command);
    return g_test_run ();
}


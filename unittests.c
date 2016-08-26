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
    g_assert_cmpstr(cfg->font, ==, "M+ 1mn regular,VL Gothic,Noto Sans Mono CJK JP 16");
    g_assert_cmpstr(cfg->title, ==, "Marmite");
    g_assert_cmpint(cfg->scrollback, ==, 200);
    g_assert_cmpint(cfg->colour_mode, ==, 0);
}

static void opt_title(void) {
    const char *title = "Hello World";
    MarmiteConfig *cfg = run_opts(3, "marmite", "-t", title);
    g_assert_nonnull(cfg);
    g_assert_cmpstr(cfg->title, ==, title);
}

static void opt_font(void) {
    const char *fontname = "Another Font";
    MarmiteConfig *cfg = run_opts(3, "marmite", "-f", fontname);
    g_assert_nonnull(cfg);
    g_assert_cmpstr(cfg->font, ==, fontname);
}

static void opt_scrollback(void) {
    MarmiteConfig *cfg = run_opts(3, "marmite", "-s", "123");
    g_assert_nonnull(cfg);
    g_assert_cmpint(cfg->scrollback, ==, 123);
}

static void opt_light(void) {
    MarmiteConfig *cfg = run_opts(2, "marmite", "-l");
    g_assert_nonnull(cfg);
    g_assert_cmpint(cfg->colour_mode, ==, 1);
}

static void opt_command(void) {
    char *argv[] = { "marmite", "foo", "-e", "bar", NULL };
    MarmiteConfig *cfg = marmite_config(4, argv, NULL);
    g_assert_nonnull(cfg);
    g_assert_cmpstr(cfg->command[0], ==, "foo");
    g_assert_cmpstr(cfg->command[1], ==, "-e");
    g_assert_cmpstr(cfg->command[2], ==, "bar");
    g_assert_null(cfg->command[3]);
    // no scrollback by default if a command is given
    g_assert_cmpint(cfg->scrollback, ==, 0);
}

int main (int argc, char *argv[]) {
    setlocale (LC_ALL, "");
    g_test_init(&argc, &argv, NULL);
    g_test_add_func("/marmite/config/default", default_config);
    g_test_add_func("/marmite/config/font", opt_font);
    g_test_add_func("/marmite/config/command", opt_command);
    g_test_add_func("/marmite/config/title", opt_title);
    g_test_add_func("/marmite/config/scrollback", opt_scrollback);
    g_test_add_func("/marmite/config/light", opt_light);
    return g_test_run ();
}


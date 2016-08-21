#include <glib.h>
#include <locale.h>
#include "config.h"

static void default_config(void) {
    char *argv[1] = { "test" };
    MarmiteConfig *cfg = marmite_config((sizeof argv / sizeof argv[0]), argv, NULL);
    g_assert_nonnull(cfg);
    g_assert_true(g_str_has_suffix(cfg->command[0], "sh"));
    g_assert_cmpstr(cfg->font, ==, "VL Gothic 16");
}

int main (int argc, char *argv[]) {
    setlocale (LC_ALL, "");
    g_test_init(&argc, &argv, NULL);
    g_test_add_func("/marmite/config/default", default_config);
    return g_test_run ();
}


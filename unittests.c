#include <glib.h>
#include <locale.h>
#include "args.h"

static void dummy(void) {
  g_assert_cmpint(2, ==, 2);
  g_assert_cmpint(3, ==, 3);
}

int main (int argc, char *argv[]) {
  setlocale (LC_ALL, "");
  g_test_init(&argc, &argv, NULL);
  g_test_add_func("/marmite/dummy", dummy);
  return g_test_run ();
}


#include <glib.h>
#include <gtk/gtk.h>
#include <vte/vte.h>
#include <locale.h>
#include "config.h"
#include "look.h"

#if VTE_CHECK_VERSION(0,37,0)
static void got_child_exited(VteTerminal *vte, gint status, GtkWindow *win) {
#else
static void got_child_exited(VteTerminal *vte, GtkWindow *win) {
#endif
    gtk_window_close(win);
}

static void got_title_changed(VteTerminal *vte, GtkWindow *win) {
    gtk_window_set_title(win, vte_terminal_get_window_title(vte));
}


int main(int argc, char *argv[]) {
    GtkWindow *window;
    VteTerminal *vte;
    MarmiteConfig *cfg;

	setlocale(LC_ALL, "");

    cfg = marmite_config(argc, argv, gtk_get_option_group(TRUE));
    if (!cfg) return 64;

    window = GTK_WINDOW(gtk_window_new(GTK_WINDOW_TOPLEVEL));
    gtk_window_set_title(window, "Marmite");
    g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), NULL);

    vte = VTE_TERMINAL(vte_terminal_new());
    vte_terminal_set_scrollback_lines(vte, 200);
    vte_terminal_set_mouse_autohide(vte, TRUE);
    marmite_look(vte);

#if VTE_CHECK_VERSION(0,37,0)
    vte_terminal_spawn_sync(vte, VTE_PTY_DEFAULT, NULL, cfg->command,
            NULL, G_SPAWN_SEARCH_PATH, NULL, NULL, NULL, NULL, NULL);
#else
    vte_terminal_fork_command_full(vte, VTE_PTY_DEFAULT, NULL, cfg->command,
            NULL, G_SPAWN_SEARCH_PATH, NULL, NULL, NULL, NULL);
#endif

    g_signal_connect(G_OBJECT(vte), "child-exited", G_CALLBACK(got_child_exited), window);
    g_signal_connect(G_OBJECT(vte), "window-title-changed", G_CALLBACK(got_title_changed), window);

    gtk_container_add(GTK_CONTAINER(window), GTK_WIDGET(vte));
    gtk_widget_show(GTK_WIDGET(vte));
    gtk_widget_show(GTK_WIDGET(window));
    gtk_main();

    return 0;
}

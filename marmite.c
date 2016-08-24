#include <glib.h>
#include <gtk/gtk.h>
#include <locale.h>
#include "config.h"
#include "term.h"

int main(int argc, char *argv[]) {
    setlocale(LC_ALL, "");

    MarmiteConfig *cfg = marmite_config(argc, argv, gtk_get_option_group(TRUE));
    if (!cfg) return 64;

    GtkWindow *window = GTK_WINDOW(gtk_window_new(GTK_WINDOW_TOPLEVEL));
    gtk_window_set_title(window, "Marmite"); // CONFIG: title
    g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), NULL);

    MarmiteHooks hooks = {
        .data = window,
        .set_title = (void*)gtk_window_set_title,
        .all_done = (void*)gtk_window_close,
    };

    GObject *vte = marmite_vte(cfg, &hooks);
    if (!vte) return 70;

    gtk_container_add(GTK_CONTAINER(window), GTK_WIDGET(vte));
    gtk_widget_show_all(GTK_WIDGET(window));
    gtk_main();

    return 0;
}

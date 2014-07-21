#include <glib.h>
#include <gtk/gtk.h>
#include <vte/vte.h>

/*
 * The Application object types
 */

#define MARMITE_APP_TYPE (marmite_app_get_type())
#define MARMITE_APP(obj) (G_TYPE_CHECK_INSTANCE_CAST((obj), MARMITE_APP_TYPE, MarmiteApp))

struct _MarmiteApp { GtkApplication parent; };
typedef struct _MarmiteApp MarmiteApp;

struct _MarmiteAppClass { GtkApplicationClass parent_class; };
typedef struct _MarmiteAppClass MarmiteAppClass;

GType marmite_app_get_type(void);
G_DEFINE_TYPE(MarmiteApp, marmite_app, GTK_TYPE_APPLICATION);

/*
 * The Application Window object types
 */

#define MARMITE_APP_WINDOW_TYPE (marmite_app_window_get_type())
#define MARMITE_APP_WINDOW(obj) (G_TYPE_CHECK_INSTANCE_CAST((obj), MARMITE_APP_WINDOW_TYPE, MarmiteAppWindow))

struct _MarmiteAppWindow { GtkApplicationWindow parent; };
typedef struct _MarmiteAppWindow MarmiteAppWindow;

struct _MarmiteAppWindowClass { GtkApplicationWindowClass parent_class; };
typedef struct _MarmiteAppWindowClass MarmiteAppWindowClass;

GType marmite_app_window_get_type(void);
G_DEFINE_TYPE(MarmiteAppWindow, marmite_app_window, GTK_TYPE_APPLICATION_WINDOW);

/*
 * The Application Window object methods
 */

static void got_child_exited(VteTerminal *vte, GtkWindow *win) {
    gtk_window_close(win);
}

static void got_title_changed(VteTerminal *vte, GtkWindow *win) {
    gtk_window_set_title(win, vte_terminal_get_window_title(vte));
}

static void marmite_app_window_init(MarmiteAppWindow *window) {
    VteTerminal *vte;
    char *cmd[] = { "bash", NULL };
    vte = VTE_TERMINAL(vte_terminal_new());
	vte_terminal_set_scrollback_lines(vte, 200);
	vte_terminal_set_mouse_autohide(vte, TRUE);
    vte_terminal_fork_command_full(vte, VTE_PTY_DEFAULT,
            NULL,
            cmd, NULL,
            G_SPAWN_SEARCH_PATH, NULL, NULL,
            NULL, NULL);
	g_signal_connect(G_OBJECT(vte), "child-exited", G_CALLBACK(got_child_exited), window);
	g_signal_connect(G_OBJECT(vte), "window-title-changed", G_CALLBACK(got_title_changed), window);
	gtk_container_add(GTK_CONTAINER(window), GTK_WIDGET(vte));
    gtk_widget_show(GTK_WIDGET(vte));
}

static void marmite_app_window_class_init(MarmiteAppWindowClass *class) {
}

MarmiteAppWindow * marmite_app_window_new(MarmiteApp *app) {
    return g_object_new(MARMITE_APP_WINDOW_TYPE, "application", app, NULL);
}

/*
 * The Application object methods
 */

static void marmite_app_init(MarmiteApp *app) {
}

static void marmite_app_activate(GApplication *app) {
    MarmiteAppWindow *win;
    win = marmite_app_window_new(MARMITE_APP(app));
    gtk_window_present(GTK_WINDOW(win));
}

static void marmite_app_class_init(MarmiteAppClass *class) {
  G_APPLICATION_CLASS (class)->activate = marmite_app_activate;
}

MarmiteApp * marmite_app_new(void) {
    return g_object_new(MARMITE_APP_TYPE,
            "application-id", "org.martian.marmite",
            "flags", G_APPLICATION_FLAGS_NONE,
            NULL);
}

/*
 * The main program
 */

int main(int argc, char *argv[]) {
    return g_application_run(G_APPLICATION(marmite_app_new()), argc, argv);
}


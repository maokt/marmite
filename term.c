#include <vte/vte.h>
#include <gdk/gdk.h>
#include "solarized_palette.h"
#include "term.h"


#if VTE_CHECK_VERSION(0,37,0)
static void got_child_exited(VteTerminal *vte, gint status, MarmiteHooks *hooks) {
#else
static void got_child_exited(VteTerminal *vte, MarmiteHooks *hooks) {
#endif
    if (hooks->all_done)
        hooks->all_done(hooks->data);
}

static void got_title_changed(VteTerminal *vte, MarmiteHooks *hooks) {
    if (hooks->set_title)
        hooks->set_title(hooks->data, vte_terminal_get_window_title(vte));
}

#if VTE_CHECK_VERSION(0,37,0)
static void scale_font(VteTerminal *vte, gdouble *increment) {
    gdouble scale = vte_terminal_get_font_scale(vte);
    scale += *increment;
    if (scale >= 0.25 && scale <= 4.0)
        vte_terminal_set_font_scale(vte, scale);
}
#endif

GObject *marmite_vte(MarmiteConfig *cfg, MarmiteHooks *hooks) {
    VteTerminal *vte = VTE_TERMINAL(vte_terminal_new());

    PangoFontDescription *font = pango_font_description_from_string(cfg->font);
    vte_terminal_set_font(vte, font);
    pango_font_description_free(font);

    vte_terminal_set_scrollback_lines(vte, cfg->scrollback);
    vte_terminal_set_mouse_autohide(vte, TRUE);

    if (hooks) {
        g_signal_connect(G_OBJECT(vte), "child-exited", G_CALLBACK(got_child_exited), hooks);
        g_signal_connect(G_OBJECT(vte), "window-title-changed", G_CALLBACK(got_title_changed), hooks);
    }

#if VTE_CHECK_VERSION(0,37,0)
    static const gdouble increase = 0.25, decrease = -0.25;
    g_signal_connect(G_OBJECT(vte), "increase-font-size", G_CALLBACK(scale_font), (gpointer)&increase);
    g_signal_connect(G_OBJECT(vte), "decrease-font-size", G_CALLBACK(scale_font), (gpointer)&decrease);

    vte_terminal_set_colors(vte,
            &solarized_palette[solarized_mode[cfg->colour_mode].fg], &solarized_palette[solarized_mode[cfg->colour_mode].bg],
            solarized_palette, solarized_palette_size);
    vte_terminal_spawn_sync(vte, VTE_PTY_DEFAULT, NULL, cfg->command,
            NULL, G_SPAWN_SEARCH_PATH, NULL, NULL, NULL, NULL, NULL);
#else
    vte_terminal_set_colors_rgba(vte,
            &solarized_palette[solarized_mode[cfg->colour_mode].fg], &solarized_palette[solarized_mode[cfg->colour_mode].bg],
            solarized_palette, solarized_palette_size);
    vte_terminal_fork_command_full(vte, VTE_PTY_DEFAULT, NULL, cfg->command,
            NULL, G_SPAWN_SEARCH_PATH, NULL, NULL, NULL, NULL);
#endif

    return G_OBJECT(vte);
}


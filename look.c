#include <vte/vte.h>
#include <gdk/gdk.h>
#include "palette.h"

static PangoFontDescription *font;

void marmite_look(VteTerminal *vte) {
#if VTE_CHECK_VERSION(0,37,0)
    vte_terminal_set_colors(vte, &palette[palette_fg], &palette[palette_bg], palette, palette_size);
#else
    vte_terminal_set_colors_rgba(vte, &palette[palette_fg], &palette[palette_bg], palette, palette_size);
#endif
    font = pango_font_description_from_string("VL Gothic 16");
    vte_terminal_set_font(vte, font);
}


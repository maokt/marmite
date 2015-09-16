#include <vte/vte.h>
#include <gdk/gdk.h>
#include "palette.h"

static PangoFontDescription *font;

void marmite_look(VteTerminal *vte) {
    vte_terminal_set_colors_rgba(vte, &palette[palette_fg], &palette[palette_bg], palette, palette_size);
    vte_terminal_set_cursor_shape(vte, VTE_CURSOR_SHAPE_IBEAM);
    font = pango_font_description_from_string("VL Gothic 16");
    vte_terminal_set_font(vte, font);
}


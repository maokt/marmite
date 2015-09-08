#include <vte/vte.h>
#include <gdk/gdk.h>
#include "palette.h"

void marmite_look(VteTerminal *vte) {
    vte_terminal_set_colors_rgba(vte, &palette[palette_fg], &palette[palette_bg], palette, palette_size);
    vte_terminal_set_cursor_shape(vte, VTE_CURSOR_SHAPE_IBEAM);
}


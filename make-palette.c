#include <gdk/gdk.h>

/* 
 * This program will output a C array of 16 GdkRGBA structures
 * for the "Solarized" 16 colour palette created by Ethan Schoonover.
 *
 * http://ethanschoonover.com/solarized
 *
 * The source is the array of #rgb values below, extracted from the Solarized table.
 *
 */

static const char * const palette[] = {
    "#073642", // base02
    "#dc322f", // red
    "#859900", // green
    "#b58900", // yellow
    "#268bd2", // blue
    "#d33682", // magenta
    "#2aa198", // cyan
    "#eee8d5", // base2
    "#002b36", // base03 (background)
    "#cb4b16", // orange
    "#586e75", // base01
    "#657b83", // base00
    "#839496", // base0 (foreground)
    "#6c71c4", // violet
    "#93a1a1", // base1
    "#fdf6e3", // base3
};

int main(void) {
    size_t n = sizeof palette / sizeof palette[0];
    printf("#ifndef _solarized_palette\n#define _solarized_palette 1\n");
    printf("static const GdkRGBA palette[%zu] = {\n", n);
    for (int i = 0; i < n; ++i) {
        GdkRGBA colour;
        gdk_rgba_parse(&colour, palette[i]);
        printf("    { %0.17f, %0.17f, %0.17f, %0.2f },\n", colour.red, colour.green, colour.blue, colour.alpha);
    }
    printf("};\n");
    printf("static const size_t palette_size = %zu;\n", n);
    printf("static const int palette_fg = %d;\n", 12);
    printf("static const int palette_bg = %d;\n", 8);
    printf("#endif\n");
}


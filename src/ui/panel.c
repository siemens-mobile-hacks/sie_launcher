#include <swilib.h>
#include "../links.h"
#include "../config.h"

void DrawPanel(LINK_LIST *links, int item_n) {
    const int x_panel = -1;
#ifdef ELKA
    const int y_panel = YDISP;
#else
    const int y_panel = 20;
#endif
    const int x2_panel = CFG.panel_width, y2_panel = ScreenH();
    void *canvas = BuildCanvas();
    DrawCanvas(canvas, x_panel, y_panel, x2_panel, y2_panel, 1);
    DrawRectangle(x_panel, y_panel, x2_panel, y2_panel, 0,
        CFG.panel_border_color, CFG.panel_bg_color);

    int i = 0;
    LINK_LIST *link = links;
    int x = x_panel, y = y_panel + 4;
    while (link) {
        const int width = GetImgWidth((int)link->link->icon);
        const int height = GetImgHeight((int)link->link->icon);
        x = (CFG.panel_width - width) / 2 + 1;
        if (i == item_n) {
            const int x_cursor = 3;
            const int y_cursor = y + (height / 2) - 8;
#ifdef ELKA
            const int x2_cursor = x_cursor + 2;
#else
            const int x2_cursor = x_cursor + 1;
#endif
            DrawRectangle(x_cursor, y_cursor, x2_cursor, y_cursor + 16, 0,
                         CFG.panel_cursor_border_color, CFG.panel_cursor_bg_color);
        }
        DrawImg(x, y, (int)link->link->icon);
        y += height + 4 + link->link->v_indent_next_link;
        i++;
        link = link->next;
    }
}

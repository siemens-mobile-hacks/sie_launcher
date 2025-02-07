#include <swilib.h>
#include <stdio.h>
#include "../links.h"

extern int CFG_PANEL_WIDTH;
extern char CFG_PANEL_BG_COLOR[], CFG_PANEL_BORDER_COLOR[];
extern char CFG_PANEL_CURSOR_BG_COLOR[], CFG_PANEL_CURSOR_BORDER_COLOR[];

void DrawPanel(LINK_LIST *links, int item_n) {
    const int x_panel = -1, y_panel = YDISP;
    const int x2_panel = CFG_PANEL_WIDTH, y2_panel = ScreenH();
    void *canvas = BuildCanvas();
    DrawCanvas(canvas, x_panel, y_panel, x2_panel, y2_panel, 1);
    DrawRectangle(x_panel, y_panel, x2_panel, y2_panel, 0,
        CFG_PANEL_BORDER_COLOR, CFG_PANEL_BG_COLOR);

    int i = 0;
    LINK_LIST *link = links;
    int x = x_panel, y = y_panel + 4;
    while (link) {
        const int width = GetImgWidth((int)link->link->icon);
        const int height = GetImgHeight((int)link->link->icon);
        x = (CFG_PANEL_WIDTH - width) / 2 + 1;
        if (i == item_n) {
            const int x_cursor = 3;
            const int y_cursor = y + (height / 2) - 8;
            DrawRectangle(x_cursor, y_cursor, x_cursor + 2, y_cursor + 16, 0,
                         CFG_PANEL_CURSOR_BORDER_COLOR, CFG_PANEL_CURSOR_BG_COLOR);
        }
        DrawImg(x, y, (int)link->link->icon);
        y += height + 4 + link->link->v_indent_next_link;
        i++;
        link = link->next;
    }
}

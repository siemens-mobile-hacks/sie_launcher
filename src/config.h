#pragma once

#include <cfg_items.h>

#pragma pack(push, 1)
typedef struct {
    const CFG_HDR cfghdr_0;
    char configs_path[128];

    const CFG_HDR cfghdr_p_b;
    const CFG_HDR cfghdr_p_0;
    int panel_width;
    const CFG_HDR cfghdr_p_1;
    char panel_bg_color[4];
    const CFG_HDR cfghdr_p_2;
    char panel_border_color[4];
    const CFG_HDR cfghdr_p_3;
    char panel_cursor_bg_color[4];
    const CFG_HDR cfghdr_p_4;
    char panel_cursor_border_color[4];
    const CFG_HDR cfg_hdr_p_e;
} CONFIG;
#pragma pack(pop)

extern CONFIG CFG;
extern char CFG_PATH[];

void InitConfig();

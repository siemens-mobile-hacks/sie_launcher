#include <cfg_items.h>

__CFG_BEGIN(0)

__root CFG_HDR cfghdr_0 = {CFG_STR_UTF8, "Configs path", 0, 127};
__root char CFG_CONFIGS_PATH[128] = "0:\\zbin\\etc\\SieLauncher\\";

__root CFG_HDR cfghdr_1 = {CFG_LEVEL, "Panel", 1, 0};
    __root CFG_HDR cfghdr_1_1 = {CFG_UINT, "Width", 0, 320 - 1};
#ifdef ELKA
    __root unsigned int CFG_PANEL_WIDTH = 60;
#else
    __root unsigned int CFG_PANEL_WIDTH = 30;
#endif
    __root CFG_HDR cfghdr_1_2 = {CFG_COLOR, "Background color", 0, 0};
    __root char CFG_PANEL_BG_COLOR[] = {0x00, 0x00, 0x00, 0x50};
    __root CFG_HDR cfghdr_1_3 = {CFG_COLOR, "Border color", 0, 0};
    __root char CFG_PANEL_BORDER_COLOR[] = {0x20, 0x20, 0x20, 0x50};
    __root CFG_HDR cfghdr_1_4 = {CFG_COLOR, "Cursor background color", 0, 0};
    __root char CFG_PANEL_CURSOR_BG_COLOR[] = {0xFF, 0x40, 0x40, 0x64};
    __root CFG_HDR cfghdr_1_5 = {CFG_COLOR, "Cursor border color", 0, 0};
    __root char CFG_PANEL_CURSOR_BORDER_COLOR[] = {0xFF, 0x40, 0x40, 0x64};

__root CFG_HDR cfghdr_1_10={CFG_LEVEL,"",0,0};

__CFG_END(0)

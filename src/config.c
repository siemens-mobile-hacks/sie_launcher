#include <swilib.h>
#include "config.h"

CONFIG CFG = {
    {CFG_STR_UTF8, "Configs path", 0, 127},
    "?:\\zbin\\etc\\SieLauncher\\",
    {CFG_LEVEL, "Panel", 1, 0},
    {CFG_UINT, "Width", 0, 320 - 1},
#ifdef ELKA
    60,
#else
    30,
#endif
    {CFG_COLOR, "Background color", 0, 0},
    {0x00, 0x00, 0x00, 0x50},
    {CFG_COLOR, "Border color", 0, 0},
    {0x20, 0x20, 0x20, 0x50},
    {CFG_COLOR, "Cursor background color", 0, 0},
    {0xFF, 0x40, 0x40, 0x64},
    {CFG_COLOR, "Cursor border color", 0, 0},
    {0xFF, 0x40, 0x40, 0x64},
    {CFG_LEVEL, "", 0, 0}
};

char CFG_PATH[] = "?:\\zbin\\etc\\SieLauncher.bcfg";

void InitConfig() {
    int8_t default_disk = (int8_t)BCFG_GetDefaultDisk();
    CFG.configs_path[0] = default_disk;
    CFG_PATH[0] = default_disk;
    if (BCFG_LoadConfig(CFG_PATH, &CFG, sizeof(CONFIG)) == -1) {
        BCFG_SaveConfig(CFG_PATH, &CFG, sizeof(CONFIG));
    }
}

#include <sie/sie.h>
#include "links.h"
#include "config.h"

int CopyData(LINK_LIST *link, const CFG_LINK *cfg_link) {
    if (cfg_link->enable) {
        link->link = malloc(sizeof(LINK));
        link->link->enable = cfg_link->enable;
        strcpy(link->link->value, cfg_link->value);
        strcpy(link->link->icon, cfg_link->icon);
        link->link->v_indent_next_link = cfg_link->v_indent_next_link;
        link->next = malloc(sizeof(LINK_LIST));
        return 1;
    }
    return 0;
}

int LoadLinks(LINK_LIST *links) {
    CFG_LINK cfg_link = {
        {CFG_CHECKBOX, "Enable", 0, 2},
        1,
        {CFG_STR_UTF8, "Name", 0, 127},
        "Main menu",
        {CFG_STR_UTF8, "Value", 0, 127},
        "MAIN_MENU",
        {CFG_STR_UTF8, "Icon", 0, 127},
        "",
        {CFG_UINT, "Vertical indent of next link", 0, 100},
        14,
    };

    int loaded = 0;
    char mask[128], path[256];
    sprintf(mask, "%s*.bcfg", CFG.configs_path);
    SIE_FILE *files = Sie_FS_FindFiles(mask);
    if (files) {
        SIE_FILE *file = Sie_FS_SortFilesByNameAsc(files, 0);
        LINK_LIST *last = NULL;
        while (file) {
            sprintf(path, "%s%s", file->dir_name, file->file_name);
            if (BCFG_LoadConfig(path, &cfg_link, sizeof(CFG_LINK)) != -1) {
                if (CopyData(links, &cfg_link)) {
                    last = links;
                    links = links->next;
                    loaded++;
                }
            }
            file = file->next;
        }
        if (last) {
            mfree(last->next);
            last->next = NULL;
        }
        Sie_FS_DestroyFiles(files);
    } else {
        sprintf(path, "%s00.bcfg", CFG.configs_path);
        if (BCFG_SaveConfig(path, &cfg_link, sizeof(CFG_LINK)) != -1) {
            if (CopyData(links, &cfg_link)) {
                loaded = 1;
                mfree(links->next);
                links->next = NULL;
            }
        }
    }
    return loaded;
}

void FreeLinks(LINK_LIST *links) {
    LINK_LIST *link = links;
    while (link) {
        void *next = link->next;
        mfree(link->link);
        mfree(link);
        link = next;
    }
}

LINK *GetLink(const LINK_LIST *links, int id) {
    int i = 0;
    while (links) {
        if (i++ == id) {
            return links->link;
        }
        links = links->next;
    }
    return NULL;
}

#include <sie/sie.h>
#include "links.h"

int CopyData(LINK_LIST *link) {
    extern int CFG_LINK_ENABLED;
    extern char CFG_LINK_VALUE[], CFG_LINK_ICON[];
    extern int CFG_LINK_V_INDENT_NEXT_LINK;

    if (CFG_LINK_ENABLED) {
        link->link = malloc(sizeof(LINK));
        link->link->enabled = CFG_LINK_ENABLED;
        strcpy(link->link->value, CFG_LINK_VALUE);
        strcpy(link->link->icon, CFG_LINK_ICON);
        link->link->v_indent_next_link = CFG_LINK_V_INDENT_NEXT_LINK;
        link->next = malloc(sizeof(LINK_LIST));
        return 1;
    }
    return 0;
}

int LoadLinks(LINK_LIST *links) {
    extern char CFG_CONFIGS_PATH[];
    __CONFIG_EXTERN(1, cfghdr_link_0);

    int loaded = 0;
    char mask[128], path[256];
    sprintf(mask, "%s*.bcfg", CFG_CONFIGS_PATH);
    SIE_FILE *files = Sie_FS_FindFiles(mask);
    if (files) {
        SIE_FILE *file = Sie_FS_SortFilesByNameAsc(files, 0);
        LINK_LIST *last = NULL;
        while (file) {
            sprintf(path, "%s%s", file->dir_name, file->file_name);
            if (Sie_Config_Load(path, __CONFIG(1, cfghdr_link_0))) {
                if (CopyData(links)) {
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
        sprintf(path, "%s01.bcfg", CFG_CONFIGS_PATH);
        if (Sie_Config_Load(path, __CONFIG(1, cfghdr_link_0))) {
            if (CopyData(links)) {
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

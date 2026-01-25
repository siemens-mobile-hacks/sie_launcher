#pragma once

#include <cfg_items.h>

#pragma pack(push, 1)
typedef struct {
    const CFG_HDR cfghdr_0;
    int enable;
    const CFG_HDR cfghdr_1;
    char name[128];
    const CFG_HDR cfghdr_2;
    char value[128];
    const CFG_HDR cfghdr_3;
    char icon[128];
    const CFG_HDR cfghdr_4;
    int v_indent_next_link;
} CFG_LINK;
#pragma pack(pop)

typedef struct {
    int enable;
    char value[128];
    char icon[128];
    int v_indent_next_link;
} LINK;

typedef struct {
    LINK *link;
    // void *prev;
    void *next;
} LINK_LIST;

int LoadLinks(LINK_LIST *links);
void FreeLinks(LINK_LIST *links);
LINK *GetLink(const LINK_LIST *links, int id);

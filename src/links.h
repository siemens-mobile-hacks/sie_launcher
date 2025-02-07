#pragma once

typedef struct {
    int enabled;
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

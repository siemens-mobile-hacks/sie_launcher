#include <cfg_items.h>

__CFG_BEGIN(1)

__root CFG_HDR cfghdr_link_0 = {CFG_CHECKBOX, "Enabled", 0, 2};
__root int CFG_LINK_ENABLED = 1;

__root CFG_HDR cfghdr_link_1 = {CFG_STR_UTF8, "Name", 0, 127};
__root char CFG_LINK_NAME[128] = "Main menu";

__root CFG_HDR cfghdr_link_2 = {CFG_STR_UTF8, "Value", 0, 127};
__root char CFG_LINK_VALUE[128] = "MAIN_MENU";

__root CFG_HDR cfghdr_link_3 = {CFG_STR_UTF8, "Icon", 0, 127};
__root char CFG_LINK_ICON[128] = "";

__root CFG_HDR cfghdr_link_4 = {CFG_UINT, "Vertical indent of next item", 0, 100};
__root int CFG_LINK_V_INDENT_NEXT_LINK = 0;

__CFG_END(1)

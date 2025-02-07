#include <swilib.h>

int GetIDLEGuiID() {
    void *idle_csm = FindCSMbyID(CSM_root()->idle_id);
    return ((int*)idle_csm)[DISPLACE_OF_IDLEGUI_ID/4];
}

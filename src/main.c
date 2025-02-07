#include <stdlib.h>
#include <swilib.h>
#include <string.h>
#include <sie/exec.h>
#include "ipc.h"
#include "idle.h"
#include "links.h"
#include "keyhook.h"
#include "conf_loader.h"
#include "ui/panel.h"

#define ELF_NAME "SieLauncher"

typedef struct {
    CSM_RAM csm;
    LINK_LIST *links;
    int item_n;
    int total_items;
} MAIN_CSM;

int CSM_ID;

const int minus11 =- 11;
unsigned short maincsm_name_body[140];

static void ReloadLinks(MAIN_CSM *csm) {
    LockSched();
    FreeLinks(csm->links);
    csm->links = malloc(sizeof(LINK_LIST));
    zeromem(csm->links, sizeof(LINK_LIST));
    csm->item_n = 0;
    csm->total_items = LoadLinks(csm->links);
    if (!csm->total_items) {
        MsgBoxError(1, (int)"Couldn't load links!");
    }
    UnlockSched();
}

static int OnMessage(CSM_RAM *data, GBS_MSG *msg) {
    extern char CFG_PATH[], CFG_CONFIGS_PATH[];

    MAIN_CSM *csm = (MAIN_CSM *)data;
    if (msg->msg == MSG_RECONFIGURE_REQ) {
        if (strcmp(CFG_PATH, msg->data0) == 0) {
            InitConfig();
            ShowMSG(1, (int)"SieLauncher config updated!");
        } else if (strncmp(CFG_CONFIGS_PATH, msg->data0, strlen(CFG_CONFIGS_PATH)) == 0) {
            ReloadLinks(csm);
            ShowMSG(1, (int)"SieLauncher reloaded links!");
        }
    }
    else if (msg->msg == MSG_IPC) {
        IPC_REQ *ipc = msg->data0;
        if (strcmpi(ipc->name_to, "IdleUpd") == 0) {
            DrawPanel(csm->links, csm->item_n);
        } else if (strcmpi(ipc->name_to, IPC_NAME) == 0) {
            IPC_DATA *ipc_data = ipc->data;
            if (msg->submess == IPC_NAVIGATE) {
                int key = (int)ipc_data->param0;
                if (key == UP_BUTTON) {
                    csm->item_n--;
                    if (csm->item_n < 0) {
                        csm->item_n = csm->total_items - 1;
                    }
                    DrawPanel(csm->links, csm->item_n);
                } else if (key == DOWN_BUTTON) {
                    csm->item_n++;
                    if (csm->item_n >= csm->total_items) {
                        csm->item_n = 0;
                    }
                    DrawPanel(csm->links, csm->item_n);
                }
            } else if (msg->submess == IPC_EXECUTE) {
                LINK *link = GetLink(csm->links, csm->item_n);
                if (link) {
                    SUBPROC(Sie_Exec_Execute, link->value);
                }
            }
            if (ipc_data) {
                mfree(ipc_data);
            }
            mfree(ipc);
        }
    }
    return 1;
}

static void OnCreate(CSM_RAM *data) {
    MAIN_CSM *csm = (MAIN_CSM *)data;
    csm->links = NULL;
    ReloadLinks(csm);
    AddKeyHook();
}

static void OnClose(CSM_RAM *data) {
    MAIN_CSM *csm = (MAIN_CSM *)data;
    FreeLinks(csm->links);
    RemoveKeyHook();
    SUBPROC((void *)kill_elf);
}

static const struct {
    CSM_DESC maincsm;
    WSHDR maincsm_name;
} MAINCSM = {
    {
        OnMessage,
        OnCreate,
#ifdef NEWSGOLD
        0,
        0,
        0,
        0,
#endif
        OnClose,
        sizeof(MAIN_CSM),
        1,
        &minus11
},
{
    maincsm_name_body,
    NAMECSM_MAGIC1,
    NAMECSM_MAGIC2,
    0x0,
    139,
    0
}
};

static void UpdateCSMname(void) {
    wsprintf((WSHDR *)(&MAINCSM.maincsm_name), ELF_NAME);
}

int main() {
    CSM_RAM *save_cmpc;
    char dummy[sizeof(MAIN_CSM)];
    UpdateCSMname();
    InitConfig();
    LockSched();
    save_cmpc = CSM_root()->csm_q->current_msg_processing_csm;
    CSM_root()->csm_q->current_msg_processing_csm = CSM_root()->csm_q->csm.first;
    CSM_ID = CreateCSM(&MAINCSM.maincsm, dummy, 0);
    CSM_root()->csm_q->current_msg_processing_csm = save_cmpc;
    UnlockSched();
    return 0;
}

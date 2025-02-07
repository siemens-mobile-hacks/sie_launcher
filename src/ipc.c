#include <stdlib.h>
#include <swilib.h>
#include "ipc.h"

static void Send(int submess, IPC_DATA *data) {
    IPC_REQ *ipc = malloc(sizeof(IPC_REQ));
    ipc->name_to = IPC_NAME;
    ipc->name_from = IPC_NAME;
    ipc->data = data;
    GBS_SendMessage(MMI_CEPID, MSG_IPC, submess, ipc);
}

void IPC_Navigate(int key) {
    IPC_DATA *ipc_data = malloc(sizeof(IPC_DATA));
    ipc_data->param0 = (void*)key;
    Send(IPC_NAVIGATE, ipc_data);
}

void IPC_Execute() {
    Send(IPC_EXECUTE, NULL);
}

#pragma once

#define IPC_NAME "SieLauncher"

typedef struct {
    void *param0;
    void *param1;
} IPC_DATA;

enum {
    IPC_NAVIGATE,
    IPC_EXECUTE,
};

void IPC_Navigate(int key);
void IPC_Execute();

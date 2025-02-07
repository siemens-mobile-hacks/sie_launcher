#include <swilib.h>
#include "ipc.h"
#include "idle.h"

int KeyHook(int submess, int msg) {
    if (IsGuiOnTop(GetIDLEGuiID()) && IsUnlocked() && !IsScreenSaver()) {
        if (msg == KEY_DOWN || msg == LONG_PRESS) {
            if (submess == UP_BUTTON || submess == DOWN_BUTTON) {
                RestartLockTimers();
                IPC_Navigate(submess);
                return KEYHOOK_BREAK;
            } else if (submess == ENTER_BUTTON) {
                IPC_Execute();
                return KEYHOOK_BREAK;
            }
        } else if (msg == KEY_UP) {
            if (submess == UP_BUTTON || submess == DOWN_BUTTON) {
                return KEYHOOK_BREAK;
            }
        }
    }
    return KEYHOOK_NEXT;
}

void AddKeyHook() {
    AddKeybMsgHook(KeyHook);
}

void RemoveKeyHook() {
    RemoveKeybMsgHook(KeyHook);
}

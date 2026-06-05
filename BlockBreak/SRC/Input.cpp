#include "DxLib.h"

char Key[256];
char OldKey[256];
char KeyFlg[256];

void InputKey() {
    memcpy(OldKey, Key, 256);
    GetHitKeyStateAll(Key);

    for (int i = 0; i < 256; i++) {
        KeyFlg[i] = Key[i] && !OldKey[i];
    }
}
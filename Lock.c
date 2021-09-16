//
// ロック/アンロック処理
//
#include "Buffer.h"

void lockBuffer(Buffer *buffer){
    buffer->isLocked = 1;
}

void unlockBuffer(Buffer *buffer){
    buffer->isLocked = 0;
}

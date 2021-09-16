/*
 * バッファの操作ロック
*/
#include "Buffer.h"

void lockBuffer(Buffer *buffer){
    buffer->isLocked = 1;
}

void unlockBuffer(Buffer *buffer){
    buffer->isLocked = 0;
}

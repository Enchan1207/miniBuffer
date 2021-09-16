/*
 * 初期化
*/
#include "Buffer.h"

int initBuffer(Buffer* buffer, unsigned int size){
    unsigned int allocateSize = size + 1; // 実際に確保されるのは、アロケートした数-1

    // バッファアイテム格納用のメモリを確保
    Item *bufmem = (Item *)calloc(allocateSize, sizeof(Item));
    if(bufmem == NULL) {
        return 1;
    }
    
    // 各アイテムを初期化
    for (int i = 0; i < allocateSize; i++){
        initItem(bufmem + i);
    }

    // プロパティ設定
    buffer->head = 0;
    buffer->tail = 0;
    buffer->size = allocateSize;
    buffer->usedSize = 0;    
    buffer->isLocked = 0;
    buffer->currentStatus = BUFFER_OK;
    buffer->data = bufmem;

    return 0;
}

int deinitBuffer(Buffer* buffer){
    free(buffer->data);
    return 0;
}

void initItem(Item* item){
    item->index = 0x00;
    item->value = 0.00;
}
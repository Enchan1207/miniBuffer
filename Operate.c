/*
 * 処理
*/
#include "Buffer.h"

/// バッファにデータを追加する。 (tail++)
///  - Parameters:
///     - buffer* : 対象のバッファ
///     - item : 追加するアイテム
///  - Return: 操作結果(バッファがいっぱい->BUFFER_FULL それ以外->BUFFER_OK)
int push(Buffer *buffer, Item item){
    int *tail = &(buffer->tail);
    int *head = &(buffer->head);

    // tailの次=head -> 満杯
    if (((*tail) + 1) % (buffer->size) == *head){
        // ロックされていればBUFFER_FULLを返す
        if (buffer->isLocked != 0){
            buffer->currentStatus = BUFFER_FULL;
            return buffer->currentStatus;
        }

        // popすることでバッファがいっぱいになるのを防ぐ
        // (headが加算されるので条件式がfalseになる)
        Item dust;
        pop(buffer, &dust);
    }

    // バッファサイズをインクリメント
    (buffer->usedSize)++;

    // 末尾に追加し、ポインタを進める 配列の終端にきたら先頭に戻る
    buffer->data[*tail] = item;
    (*tail)++;
    if (*tail >= buffer->size){
        *tail = 0;
    }
    buffer->currentStatus = BUFFER_OK;
    return buffer->currentStatus;
}

/// バッファからデータを取り出す。 (head++)
///  - Parameters:
///     - buffer* : 対象のバッファ
///     - item* : 取り出したアイテムのデータ
///  - Return: 操作結果(バッファが空->BUFFER_EMPTY それ以外->BUFFER_OK)
int pop(Buffer *buffer, Item *item){
    int *tail = &(buffer->tail);
    int *head = &(buffer->head);

    // head==tail -> キューは空
    if (*head == *tail){
        buffer->currentStatus = BUFFER_EMPTY;
        return buffer->currentStatus;
    }

    // バッファサイズをデクリメント
    (buffer->usedSize)--;

    // 先頭から取り出し、ポインタを進める 配列の終端にきたら先頭に戻る
    *item = buffer->data[*head];
    (*head)++;
    if (*head >= buffer->size){
        *head = 0;
    }
    buffer->currentStatus = BUFFER_OK;
    return buffer->currentStatus;
}

/// バッファのサイズを取得する。
///  - Parameters:
///     - buffer* : 対象のバッファ
unsigned int getBufSize(Buffer *B){
    return B->size - 1;
}

/// バッファから非破壊でデータを取り出す。
///  - Parameters:
///     - buffer* : 対象のバッファ
///     - advanced : バッファの先頭からのオフセット
///     - item* : 参照するアイテムのデータ
///  - Return: 操作結果(オフセット範囲外->BUFFER_OVER, それ以外->BUFFER_OK)
int getItemAt(Buffer *buffer, unsigned int advanced, Item *item){
    // バッファの情報を取得
    int size = (buffer->size);
    int usedSize = (buffer->usedSize);
    int head = (buffer->head);
    
    // 添字の有効範囲は0~usedSize -1
    if(advanced >= usedSize){
        return BUFFER_OVER;
    }

    // headにadvanceを足した位置の値を返す
    *item = buffer->data[(head + advanced) % size];
    return BUFFER_OK;
}

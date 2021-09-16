/*
 * FIFOキュー 
*/
#ifndef _BUFFER_H_
#define _BUFFER_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* -------- */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define NDEBUG

// #define BUFFER_SIZE 100

#define BUFFER_OK 0
#define BUFFER_FULL 1
#define BUFFER_EMPTY 2
#define BUFFER_OVER 3

#ifndef uint8_t
    #define uint8_t unsigned char
#endif

/* -------- */
typedef struct item {
    int index;
    double value;
} Item;

typedef struct buffer {
    // インデックス変数
    int head;
    int tail;

    // 状態変数
    unsigned int size; // バッファのサイズ
    unsigned int usedSize; // 使用済みのサイズ(=push回数-pop回数)
    unsigned int isLocked; // 0以外の値を代入するとバッファがロックされる
    int currentStatus; // 最後にバッファを操作した時の状態

    // 本体
    Item *data;

} Buffer;

/* -------- */

// Initializer.c
int initBuffer(Buffer* buffer, unsigned int length);
int deinitBuffer(Buffer* buffer);
void initItem(Item *item);

// Operate.c
int push(Buffer* buffer, Item item);
int pop(Buffer* buffer, Item* item);
int getItemAt(Buffer* buffer, unsigned int advanced, Item* item);
unsigned int getBufSize(Buffer* B);

// Lock.c
void lockBuffer(Buffer *buffer);
void unlockBuffer(Buffer *buffer);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _BUFFER_H_ */
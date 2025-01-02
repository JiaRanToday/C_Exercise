#ifndef _QUEUE_H_
#define _QUEUE_H_
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 256
typedef int QElemType;
typedef struct {
  int list[MAX_SIZE];
  int front;
  int tail;
} SqQueue;
typedef enum { ERROR = -1, FALSE, TRUE } state;
state InitQueue(SqQueue *Q);
int QueueLength(SqQueue *Q);
state ClearQueue(SqQueue *Q);
state DestroyQueue(SqQueue *Q);
state QueueEmpty(SqQueue *Q);
state QueueFull(SqQueue *Q);
state GetHead(SqQueue *Q, QElemType *e);
state EnQueue(SqQueue *Q, QElemType e);
state DeQueue(SqQueue *Q, QElemType *e);
#endif

#include "Queue.h"
state InitQueue(SqQueue *Q) {
  if (Q == NULL) {
    return ERROR;
  }
  Q->front = 0;
  Q->tail = 0;
  return TRUE;
}
int QueueLength(SqQueue *Q) {
  return (Q->tail - Q->front + MAX_SIZE) % MAX_SIZE;
}
state ClearQueue(SqQueue *Q) {
  if (Q == NULL) {
    return ERROR;
  }
  Q->front = Q->tail = 0;
  return TRUE;
}
state DestroyQueue(SqQueue *Q) {
  if (Q == NULL) {
    return FALSE;
  }
  ClearQueue(Q);
  return TRUE;
}
state QueueEmpty(SqQueue *Q) {
  if (Q == NULL) {
    return ERROR;
  }
  return (Q->front == Q->tail) ? TRUE : FALSE;
}
state QueueFull(SqQueue *Q) {
  if (Q == NULL) {
    return ERROR;
  }
  return (Q->tail + 1) % MAX_SIZE == Q->front ? TRUE : FALSE;
}
state GetHead(SqQueue *Q, QElemType *e) {
  if (Q == NULL || QueueEmpty(Q))
    return ERROR;
  *e = Q->list[Q->front];
  return TRUE;
}

state EnQueue(SqQueue *Q, QElemType e) {
  if (Q == NULL || QueueFull(Q))
    return ERROR;
  Q->list[Q->tail] = e;
  Q->tail = (Q->tail + 1) % MAX_SIZE;
  return TRUE;
}
state DeQueue(SqQueue *Q, QElemType *e) {
  if (Q->front == Q->tail)
    return ERROR;
  *e = Q->list[Q->front];
  Q->front = (Q->front + 1) % MAX_SIZE;
  return TRUE;
}

#include <stdio.h>
#include <string.h>
#define MAXSIZE 256
typedef int SElemType;
typedef struct {
  SElemType data[MAXSIZE];
  int top1;
  int top2;
} SqDoubleStack;

typedef enum { ERROR = -1, FALSE, TRUE } Status;

Status InitSqDoubleStack(SqDoubleStack *S) {
  if (S == NULL) {
    return ERROR;
  }
  memset(S->data, 0, MAXSIZE);
  S->top1 = -1;
  S->top2 = MAXSIZE;
  return TRUE;
}
Status push(SqDoubleStack *S, SElemType *e, int stackNumber) {
  if (S->top1 + 1 == S->top2) {
    return NULL;
  }
  if (stackNumber == 1) {
    S->data[++(S->top1)] = *e;
  } else if (stackNumber == 2) {
    S->data[--(S->top2)] = *e;
  }
  return TRUE;
}
Status pop(SqDoubleStack *S, SElemType *e, int stackNumber) {
  if (S->top1 + 1 == S->top2) {
    return ERROR;
  }
  if (stackNumber == 1) {
    if (S->top1 == -1)
      return ERROR;
    *e = S->data[(S->top1)--];
  } else if (stackNumber == 2) {
    if (S->top2 == MAXSIZE)
      return ERROR;
    *e = S->data[(S->top2)++];
  }
  return TRUE;
}

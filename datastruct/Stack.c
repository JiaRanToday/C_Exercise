#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STACK 256
typedef int SElemType;
typedef struct {
  SElemType data[MAX_STACK];
  int top;
} SqStack;
typedef enum { ERROR = -1, FALSE, TRUE } Status;
Status InitStack(SqStack *S) {
  if (S == NULL) {
    S = (SqStack *)malloc(sizeof(SqStack));
  }
  memset(S->data, 0, MAX_STACK);
  S->top = -1;
  return TRUE;
}
Status DestoryStack(SqStack *S) {
  if (S == NULL) {
    return ERROR;
  }
  free(S);
  return TRUE;
}
Status ClearStack(SqStack *S) {
  if (S == NULL) {
    return ERROR;
  }
  S->top = -1;
  return TRUE;
}
Status StackEmpty(SqStack *S) {
  if (S == NULL) {
    return ERROR;
  }
  if (S->top == -1) {
    return TRUE;
  }
  return FALSE;
}
Status GetTop(SqStack *S, SElemType *e) {
  if (S == NULL || S->top == -1) {
    return ERROR;
  }
  *e = S->data[S->top];
  return TRUE;
}
Status Push(SqStack *S, SElemType e) {
  if (S->top == MAX_STACK - 1) {
    return ERROR;
  }
  S->top++;
  S->data[S->top] = e;
  return TRUE;
}
Status pop(SqStack *S, SElemType *e) {
  if (S->top == -1) {
    return ERROR;
  }
  *e = S->data[S->top];
  S->top--;
  return TRUE;
}
int StackLength(SqStack *S) { return S->top + 1; }

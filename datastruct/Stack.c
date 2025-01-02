#include "Stack.h"
Status InitStack(SqStack *S) {
  if (S == NULL) {
    return ERROR;
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
  return (S->top == -1) ? TRUE : FALSE;
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
  S->data[++(S->top)] = e;
  return TRUE;
}
Status pop(SqStack *S, SElemType *e) {
  if (S == NULL && S->top == -1) {
    return ERROR;
  }
  *e = S->data[S->top--];
  return TRUE;
}
int StackLength(SqStack *S) { return S->top + 1; }

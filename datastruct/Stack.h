#ifndef _STACK_H_
#define _STACK_H_
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
Status InitStack(SqStack *S);
Status ClearStack(SqStack *S);
Status StackEmpty(SqStack *S);
Status GetTop(SqStack *S, SElemType *e);
Status Push(SqStack *S, SElemType e);
Status pop(SqStack *S, SElemType *e);
int StackLength(SqStack *S);
#endif

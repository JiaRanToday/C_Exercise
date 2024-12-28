#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef int SElemType;
typedef struct StackNode {
  SElemType data;
  struct StackNode *next;
} StackNode, *LinkStackPtr;

typedef struct LinkStack {
  LinkStackPtr top;
  int count;
} LinkStack;
static LinkStack *ptr;
typedef enum { ERROR = -1, FALSE, TRUE } State;
State InitLinkStack(LinkStack *LS) {
  if (LS == NULL) {
    return ERROR;
  }
  LS->top = NULL;
  int count = 0;
  return TRUE;
}
State push(LinkStack *LS, SElemType data) {
  if (LS == NULL) {
    return ERROR;
  }
  LinkStackPtr node = (LinkStackPtr)malloc(sizeof(StackNode));
  node->data = data;
  node->next = LS->top;
  LS->top = node;
  LS->count++;
  return TRUE;
}
State pop(LinkStack *LS, SElemType *e) {
  if (LS == NULL) {
    return ERROR;
  }
  LinkStackPtr node = LS->top;
  *e = node->data;
  LS->top = LS->top->next;
  free(node);
  LS->count--;
  return TRUE;
}

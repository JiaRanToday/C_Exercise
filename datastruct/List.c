#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

#define MAX_SIZE 1024
typedef struct {
  int list[MAX_SIZE];
  int size;
} List;

typedef enum {
  FALSE,
  OK,
} status;
void InitList(List *L) { L->size = 0; }
status IsListEmpty(List *L) {
  if (L == NULL) {
    return FALSE;
  }
  return (L->size == 0) ? OK : FALSE;
}
status ClearList(List *L) {
  if (L == NULL) {
    return FALSE;
  }
  L->size = 0;
  return OK;
}
status GetELem(List *L, int i, int *e) {
  if (L == NULL || i < 1 || i >= L->size) {
    return FALSE;
  }
  *e = L->list[i - 1];
  return OK;
}
int LocateElem(const List *L, int e) {
  if (L == NULL) {
    return FALSE;
  }
  int index = L->size - 1;
  while (index-- >= 0) {
    if (L->list[index] == e)
      return index + 1;
  }
  return FALSE;
}
status ListInsert(List *L, int i, int *e) {
  if (L == NULL || i < 1 || i > L->size + 1 || L->size == MAX_SIZE) {
    return FALSE;
  }
  for (int index = L->size - 1; index >= i - 1; index--) {
    L->list[index + 1] = L->list[index];
  }
  L->list[i - 1] = *e;
  L->size++;
  return OK;
}
status ListDelete(List *L, int i, int *e) {
  if (L == NULL || i < 1 || i > L->size) {
    return FALSE;
  }
  *e = L->list[i - 1];
  for (int index = i - 1; index < L->size - 1; index++) {
    L->list[index] = L->list[index + 1];
  }
  L->size--;
  return OK;
}
int ListLength(List *L) {
  if (L == NULL) {
    return FALSE;
  }
  return L->size;
}

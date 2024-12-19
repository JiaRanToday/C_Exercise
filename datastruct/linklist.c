#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef int ElemType;
typedef struct Node {
  ElemType data;
  struct Node *next;
} Node;
typedef enum { ERROR = -1, FALSE, TRUE } Status;
typedef struct Node *Linklist;
Status GetElem(Linklist L, int i, ElemType *e) {
  if (L == NULL || i < 1) {
    return ERROR;
  }
  int j;
  Linklist p;
  p = *L;
  j = 1;
  while (p && j < i) {
    p = p->next;
    ++j;
  }
  if (p == NULL || j > i)
    return ERROR;
  *e = p->data;
  return TRUE;
}
Status InsertNode(Linklist *L, int i, ElemType *e) {
  if (L == NULL || i < 1) {
    return ERROR;
  }
  int j;
  Linklist p, node;
  p = *L;
  j = 1;
  while (p && j < i) {
    p = p->next;
    ++j;
  }
  if (p == NULL || j > i) {
    return ERROR;
  }
  node = (Linklist)malloc(sizeof(Node));
  node->data = *e;
  node->next = p->next;
  p->next = node;
  return TRUE;
}
Status DeleteNode(Linklist *L, int i, ElemType *e) {
  if (L == NULL || i < 1)
    return ERROR;
  int j;
  Linklist p, node;
  p = *L;
  j = 1;
  while (p && j < i - 1) {
    p = p->next;
    ++j;
  }
  if (p == NULL || p->next == NULL) {
    return ERROR;
  }
  node = p->next;
  p->next = node->next;
  free(node);
  return TRUE;
}
void CreateListHead(Linklist *L, int n) {
  if (L == NULL || n < 1) {
    return;
  }
  srand(time(0));
  int i;
  *L = (Linklist)malloc(sizeof(Node));
  (*L)->next = NULL;
  Linklist p;
  for (int i = 0; i < n; i++) {
    p = (Linklist)malloc(sizeof(Node));
    p->data = rand() % 100 + 1;
    p->next = (*L)->next;
    (*L)->next = p;
  }
}
void CreateListTail(Linklist *L, int n) {
  if (L == NULL || n < 1) {
    return;
  }
  srand(time(0));
  int i;
  *L = (Linklist)malloc(sizeof(Node));
  (*L)->next = NULL;
  Linklist p, r;
  r = *L;
  for (int i = 0; i < n; i++) {
    p = (Linklist)malloc(sizeof(Node));
    p->data = rand() % 100 + 1;
    r->next = p;
    r = p;
  }
  r->next = NULL;
}
Status ClearList(Linklist *L) {
  if (L == NULL) {
    return ERROR;
  }
  Linklist p, q;
  p = (*L)->next;
  while (p) {
    q = p->next;
    free(p);
    p = q;
  }
  (*L)->next = NULL;
  return TRUE;
}

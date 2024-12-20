#include <stdbool.h>
#include <stdio.h>

#define MAXSIZE 1000
typedef int ElemType;
typedef struct {
  ElemType data;
  int cur;
} Component, StaticLinkList[MAXSIZE];
typedef enum { ERROR = -1, FALSE, OK } Status;
Status InitList(StaticLinkList space) {
  int i;
  for (i = 0; i < MAXSIZE - 1; i++) {
    space[i].cur = i + 1;
  }
  space[MAXSIZE - 1].cur = 0;
  return OK;
}
int Malloc_SLL(StaticLinkList space) {
  int i = space[0].cur;
  if (space[0].cur)
    space[0].cur = space[i].cur;
  return i;
}
int ListLength(StaticLinkList L) {
  int j = 0;
  int i = L[MAXSIZE - 1].cur;
  while (i) {
    i = L[i].cur;
    j++;
  }
  return j;
}
Status ListInsert(StaticLinkList L, int i, ElemType e) {
  if (i < 1 || i > ListLength(L) + 1) {
    return ERROR;
  }
  int k = MAXSIZE - 1;
  int j = Malloc_SLL(L);
  if (j) {
    L[j].data = e;
    for (int l = 1; l <= i - 1; l++) {
      k = L[k].cur;
    }
    L[j].cur = L[k].cur;
    L[k].cur = j;
  }
  return OK;
}
void Free_SSL(StaticLinkList space, int i) {
  space[i].cur = space[0].cur;
  space[0].cur = i;
}
Status ListDelete(StaticLinkList L, int i) {
  if (i < 1 || i > ListLength(L)) {
    return ERROR;
  }
  int hd = MAXSIZE - 1;
  int cur = L[hd].cur;
  int pt = 1;
  while (pt++ < i - 1) {
    cur = L[cur].cur;
  }
  int l = L[cur].cur;
  L[cur].cur = L[l].cur;
  Free_SSL(L, l);
  return OK;
}

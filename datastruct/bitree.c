#include "bitree.h"
#include <stdio.h>
#include <stdlib.h>

Status visit(TElemType c) {
  printf("%d", c);
  return OK;
}

Status InitBiTree(SqBiTree T) {
  int i;
  for (i = 0; i < MAX_TREE_SIZE; i++) {
    T[i] = Nil;
  }
  return OK;
}

Status CreateBiTree(SqBiTree T) {}

Status BiTreeEmpty(SqBiTree T) {}

int BiTreeDepth(SqBiTree T) {}

Status Root(SqBiTree T, TElemType *e) {}

TElemType Value(SqBiTree T, Position e) {}

Status Assign(SqBiTree T, Position e, TElemType value);

TElemType Parent(SqBiTree T, TElemType e);

TElemType LeftChild(SqBiTree T, TElemType e);

TElemType RightChild(SqBiTree T, TElemType e);

TElemType LeftSibling(SqBiTree T, TElemType e);

TElemType RightSibling(SqBiTree T, TElemType e);

void PreTraverse(SqBiTree T, int e);

Status PreOrderTraverse(SqBiTree T);

void InTraverse(SqBiTree T, int e);

Status InOrderTraverse(SqBiTree T);

void PostTraverse(SqBiTree T, int e);

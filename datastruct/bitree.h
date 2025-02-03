#ifndef BITREE_H_
#define BITREE_H_
#include <stdio.h>
#include <stdlib.h>

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0

#define MAXSIZE 100
#define MAX_TREE_SIZE 100

typedef int Status;
typedef int TElemType;
typedef TElemType SqBiTree[MAX_TREE_SIZE];

typedef struct {
  int level, order;
} Position;

TElemType Nil = 0;

Status visit(TElemType c);
Status InitBiTree(SqBiTree T);
Status CreateBiTree(SqBiTree T);

#define CreateBiTree InitBiTree

Status BiTreeEmpty(SqBiTree T);
int BiTreeDepth(SqBiTree T);
Status Root(SqBiTree T, TElemType *e);
TElemType Value(SqBiTree T, Position e);
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

#endif

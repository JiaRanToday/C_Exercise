#include <stdbool.h>
#include <stdio.h>

typedef int ElemType;
typedef struct Node {
  ElemType data;
  struct Node *prior;
  struct Node *next;
} Node;

typedef enum { ERROR = -1, FALSE, TRUE } Status;
typedef Node *DoubleLinkList;

Status GetElem()

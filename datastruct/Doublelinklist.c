#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef int ElemType;
typedef struct Node {
  ElemType data;
  struct Node *prior;
  struct Node *next;
} Node;

typedef struct {
  Node *head;
  Node *tail;
} DoublyLinkList;

typedef enum { ERROR = -1, FALSE, TRUE } Status;

void InitList(DoublyLinkList *list) {
  if (list == NULL) {
    list = (DoublyLinkList *)malloc(sizeof(DoublyLinkList));
  }
  list->head = NULL;
  list->tail = NULL;
}
Status InsertHead(DoublyLinkList *list, ElemType data) {
  if (list == NULL) {
    return ERROR;
  }
  Node *newNode = (Node *)malloc(sizeof(Node));
  newNode->data = data;
  newNode->prior = NULL;
  newNode->next = list->head;
  if (list->head != NULL) {
    list->head->prior = newNode;
  } else {
    list->tail = newNode;
  }
  list->head = newNode;
  return TRUE;
}

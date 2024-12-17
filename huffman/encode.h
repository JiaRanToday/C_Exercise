#ifndef ENCODE_H_
#define ENCODE_H_
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef unsigned char uint8_t;
typedef unsigned int uint32_t;
typedef unsigned short uint16_t;
typedef struct MinHeapNode {
  uint8_t byte;
  uint32_t freq;
  bool isleaf;
  struct MinHeapNode *left;
  struct MinHeapNode *right;
} MinHeapNode, huffTreeNode;
typedef struct MinHeap {
  int size;
  int capacity;
  MinHeapNode **heap;
} MinHeap;

int calculateTreeDepth(huffTreeNode *root);
void printHuffTree(huffTreeNode *huffroot, int space);
void printHuffCodeBook();
void printHeapNode(MinHeapNode *node);
void printMinHeap(MinHeap *heap);
void printFreqTable(uint32_t *freqTable);
void initFreqTable(uint32_t *freqTable, uint8_t *data, int datasize);
MinHeapNode *createHeapNode(uint8_t byte, uint32_t freq, bool isleaf);
MinHeap *createHeap(int capacity);
void freeHeap(MinHeap *heap);
// void freeHeapNode(MinHeapNode *node);
// int getParent(int index);
// int getChildLeft(int index);
// int getChildRight(int index);
// void swapHeapNode(MinHeapNode **node1, MinHeapNode **node2);
// void heapifyup(MinHeap *heap, int index);
// void heapifydown(MinHeap *heap, int index);
// void pushHeap(MinHeap *heap, MinHeapNode *node);
// MinHeapNode *popHeap(MinHeap *heap);
void initMinHeap(MinHeap *minheap, uint32_t *freqTable);
// huffTreeNode *createHuffNode(uint8_t byte, uint32_t freq, bool isleaf,
                             // huffTreeNode *left, huffTreeNode *right);
huffTreeNode *plantHuffTree(MinHeap *heap);
void freeHuffTree(huffTreeNode *root);
void initCodeBook(uint8_t *codebook[], int size);
// void generateHuffcode(huffTreeNode *node, char *code, int index,
                      // uint8_t *codebook[]);
void generateHuffTreecodebook(huffTreeNode *root, uint8_t *codebook[]);
void freeCodeBook(uint8_t *codebook[], int size);
int countCodeBook(uint8_t *codebook);
void verifyPrefixCodes(uint8_t *codebook[]);
uint32_t getEncodeDataLen(uint8_t *codebook[], uint32_t *freqTable);
// uint8_t *getEncodeData(uint8_t *codebook[], uint8_t *data, uint32_t datasize,
                       // uint32_t *freqTable);
void freeEncodeData(uint8_t *encodeData);
uint16_t read_uint16_le(const uint8_t *buffer, int index);
// uint8_t *packageEncode(uint32_t datasize, uint32_t *freqTable,
                       // uint8_t *encodedata, uint32_t encodedataLen,
                       // uint32_t *getCompreSize);
uint8_t *compressProcess(uint8_t *data, int datasize, uint32_t *getCompreSize);
#endif

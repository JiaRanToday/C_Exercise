#include "encode.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_TABLE 256
#define MAX_CODE 256
#define SECTION_1 4
#define SECTION_2 2
#define SECTION_3 1
#define SECTION_4 2
#define SECTION_5 1

static uint8_t *CodeBook[256];
// unsigned char data[20];
void initFreqTable(uint32_t *freqTable, uint8_t *data, int datasize) {
  memset(freqTable, 0, 256 * sizeof(uint32_t));
  for (int i = 0; i < datasize; i++) {
    freqTable[data[i]]++;
  }
}
MinHeapNode *createHeapNode(uint8_t byte, uint32_t freq, bool isleaf) {
  MinHeapNode *node = (MinHeapNode *)malloc(sizeof(MinHeapNode));
  node->byte = byte;
  node->freq = freq;
  node->isleaf = isleaf;
  node->left = NULL;
  node->right = NULL;
  return node;
}
MinHeap *createHeap(int capacity) {
  MinHeap *heap = (MinHeap *)malloc(sizeof(MinHeap));
  heap->capacity = capacity;
  heap->size = 0;
  heap->heap = malloc(sizeof(MinHeapNode *) * capacity);
  if (heap == NULL || heap->heap == NULL) {
    printf("Memory allocation failed!\n");
    return NULL;
  }
  return heap;
}
void freeHeapNode(MinHeapNode *node) { free(node); }

void freeHeap(MinHeap *heap) {
  if (heap == NULL)
    return;
  for (int i = 0; i < heap->size; i++) {
    freeHeapNode(heap->heap[i]);
  }
  free(heap->heap);
  free(heap);
  printf("free heap success\r\n");
}
int getParent(int index) { return (index - 1) / 2; }
int getChildLeft(int index) { return 2 * index + 1; }
int getChildRight(int index) { return 2 * index + 2; }
void swapHeapNode(MinHeapNode **node1, MinHeapNode **node2) {
  MinHeapNode *tempnode = *node1;
  *node1 = *node2;
  *node2 = tempnode;
}
void heapifyup(MinHeap *heap, int index) {
  if (heap->size <= 0) {
    return;
  }
  int father = getParent(index);
  int tempindex = index;
  if (tempindex > 0 && heap->heap[father]->freq > heap->heap[tempindex]->freq) {
    tempindex = father;
  }
  if (tempindex != index) {
    swapHeapNode(&heap->heap[tempindex], &heap->heap[index]);
    heapifyup(heap, tempindex);
  }
}
void heapifydown(MinHeap *heap, int index) {
  if (heap->size <= 0) {
    return;
  }
  int left = getChildLeft(index);
  int right = getChildRight(index);
  int tempindex = index;
  if (left < heap->size &&
      heap->heap[left]->freq < heap->heap[tempindex]->freq) {
    tempindex = left;
  }
  if (right < heap->size &&
      heap->heap[right]->freq < heap->heap[tempindex]->freq) {
    tempindex = right;
  }
  if (tempindex != index) {
    swapHeapNode(&heap->heap[tempindex], &heap->heap[index]);
    heapifydown(heap, tempindex);
  }
}
void pushHeap(MinHeap *heap, MinHeapNode *node) {
  if (heap->size == heap->capacity) {
    printf("heap is full!\r\n");
    return;
  }
  heap->heap[heap->size] = node;
  heap->size++;
  heapifyup(heap, heap->size - 1);
}
MinHeapNode *popHeap(MinHeap *heap) {
  if (heap->size == 0) {
    printf("heap is empty!\r\n");
    return NULL;
  }
  MinHeapNode *root = heap->heap[0];
  heap->heap[0] = heap->heap[heap->size - 1];
  heap->size--;
  heapifydown(heap, 0);
  return root;
}
void printHeapNode(MinHeapNode *node) {
  if (node != NULL) {
    printf("Byte: %d, Freq: %u, IsLeaf: %d\n", node->byte, node->freq,
           node->isleaf);
  }
}
void printMinHeap(MinHeap *heap) {
  if (heap == NULL || heap->size == 0) {
    printf("Heap is empty!\n");
    return;
  }
  printf("MinHeap contents:\n");
  for (int i = 0; i < heap->size; i++) {
    printf("Index %d: ", i);
    printHeapNode(heap->heap[i]);
  }
}
void initMinHeap(MinHeap *minheap, uint32_t *freqTable) {
  for (int i = 0; i < MAX_TABLE; i++) {
    if (freqTable[i] != 0) {
      MinHeapNode *minNode = createHeapNode((uint8_t)i, freqTable[i], true);
      pushHeap(minheap, minNode);
      // printMinHeap(minheap);
    }
  }
}
huffTreeNode *createHuffNode(uint8_t byte, uint32_t freq, bool isleaf,
                             huffTreeNode *left, huffTreeNode *right) {
  huffTreeNode *node = (huffTreeNode *)malloc(sizeof(huffTreeNode));
  node->byte = byte;
  node->freq = freq;
  node->isleaf = isleaf;
  node->left = left;
  node->right = right;
  return node;
}
huffTreeNode *plantHuffTree(MinHeap *heap) {
  if (heap->size == 1) {
    return popHeap(heap);
  }
  huffTreeNode *leftNode = popHeap(heap);
  huffTreeNode *rightNode = popHeap(heap);
  uint32_t combin_freq = leftNode->freq + rightNode->freq;
  huffTreeNode *interHuffNode =
      createHuffNode(0, combin_freq, false, leftNode, rightNode);
  pushHeap(heap, interHuffNode);
  return plantHuffTree(heap);
}
void freeHuffTree(huffTreeNode *root) {
  if (root == NULL) {

    printf("free success or root is NULL\r\n");
    return;
  }
  freeHuffTree(root->left);
  freeHuffTree(root->right);
  free(root);
}
void initCodeBook(uint8_t *codebook[], int size) {
  for (int i = 0; i < size; i++) {
    codebook[i] = NULL;
  }
}
void generateHuffcode(huffTreeNode *node, char *code, int index,
                      uint8_t *codebook[]) {
  if (node == NULL)
    return;
  if (node->isleaf) {
    code[index] = '\0';
    printf("huffnode = %d freq = %d\r\n", node->byte, node->freq);
    codebook[node->byte] = (uint8_t *)strdup(code);
  }
  code[index] = '0';
  generateHuffcode(node->left, code, index + 1, codebook);
  code[index] = '1';
  generateHuffcode(node->right, code, index + 1, codebook);
}
void generateHuffTreecodebook(huffTreeNode *huffroot, uint8_t *codebook[]) {
  huffTreeNode *root = huffroot;
  char code[256];
  generateHuffcode(root, code, 0, codebook);
}
void freeCodeBook(uint8_t *codebook[], int size) {
  if (codebook == NULL) {
    printf("codebook is not malloc any node");
    return;
  }
  for (int i = 0; i < size; i++) {
    free(codebook[i]);
  }
  printf("free codebook success\r\n");
}
int countCodeBook(uint8_t *codebook) { return strlen((char *)codebook); }
bool isPrefix(const uint8_t *s1, const uint8_t *s2) {
  while (*s1 && *s2) {
    if (*s1 != *s2)
      return false;
    s1++;
    s2++;
  }
  if (*s1 == '\0')
    return true;
  return false;
}
void verifyPrefixCodes(uint8_t *codebook[]) {
  bool conflict = false;
  for (int i = 0; i < 256; i++) {
    if (codebook[i] == NULL)
      continue;
    for (int j = 0; j < 256; j++) {
      if (i == j || codebook[j] == NULL)
        continue;
      if (isPrefix(codebook[i], codebook[j])) {
        printf("Error: Code for byte 0x%02x (%s) is a prefix of byte %d's code "
               "(%s).\n",
               i, codebook[i], j, codebook[j]);
        conflict = true;
      }
    }
  }
  if (!conflict) {
    printf("所有编码均满足前缀码性质。\n");
  }
}
uint32_t getEncodeDataLen(uint8_t *codebook[], uint32_t *freqTable) {
  if (codebook == NULL || freqTable == NULL) {
    printf("getEncodeDatalen failed\r\n");
    return 0;
  }
  uint32_t length = 0;
  for (int i = 0; i < 256; i++) {
    if (freqTable[i] > 0) {
      int count = countCodeBook(codebook[i]);
      length += count * freqTable[i];
    }
  }
  printf("countEncode =%d\r\n", length);
  return length;
}
uint8_t *getEncodeData(uint8_t *codebook[], uint8_t *data, uint32_t datasize,
                       uint32_t *freqTable) {
  uint32_t encodeDataLength = getEncodeDataLen(codebook, freqTable);
  uint8_t *encodeData = malloc(encodeDataLength + 1);
  if (encodeData == NULL) {
    printf("encodedata malloc error\r\n");
    return NULL;
  }
  memset(encodeData, '\0', encodeDataLength);
  int index = 0;
  for (int i = 0; i < datasize; i++) {
    if (codebook[data[i]] != NULL) {
      // printf("codebook = %s\n", codebook[data[i]]);
      int count = strlen((char *)codebook[data[i]]);
      memcpy(encodeData + index, codebook[data[i]], count);
      index += count;
    }
  }
  return encodeData;
}
void freeEncodeData(uint8_t *encodeData) {
  if (encodeData == NULL) {
    printf("encodeData is empty");
    return;
  }
  free(encodeData);
  printf("free encode sucess");
}
uint16_t read_uint16_le(const uint8_t *buffer, int index) {
  return (uint16_t)((buffer[index] & 0xFFFF) | (buffer[index + 1]) << 8);
}
uint8_t getFreqTableLength(uint32_t *freqTable) {
  if (freqTable == NULL) {
    printf("[getFreqTableLength] freqTable is null\r\n");
    return 0;
  }
  uint8_t freqTablelength = 0;
  int MaxElement = MAX_TABLE;
  while (MaxElement--) {
    if (freqTable[MaxElement] > 0)
      freqTablelength++;
  }
  return freqTablelength;
}
uint8_t *packageEncode(uint32_t datasize, uint32_t *freqTable,
                       uint8_t *huffmanBytes, uint32_t encodeBitLength,
                       uint32_t *getCompreSize) {
  if (huffmanBytes == NULL || freqTable == NULL) {
    printf("[packageEncode] encodedata or freqTable is null\r\n");
    return NULL;
  }
  uint8_t *combinString = NULL;
  uint16_t freqTablelength = getFreqTableLength(freqTable);
  printf("freeTablelength = %d\r\n", freqTablelength);
  int huffmanByteslength =
      encodeBitLength % 8 > 0 ? encodeBitLength / 8 + 1 : encodeBitLength / 8;
  uint8_t bitMatch = encodeBitLength % 8 > 0 ? 8 - encodeBitLength % 8 : 0;
  *getCompreSize = SECTION_1 + SECTION_2 +
                   freqTablelength * (SECTION_3 + SECTION_4) + SECTION_5 +
                   huffmanByteslength;
  combinString = malloc(*getCompreSize);
  if (combinString == NULL) {
    printf("combinString malloc error\r\n");
    return NULL;
  }
  memset(combinString, 0, *getCompreSize);
  memcpy(combinString, &datasize, sizeof(uint32_t));
  memcpy(&combinString[SECTION_1], &freqTablelength, sizeof(uint16_t));
  int counter = 0;
  for (int i = 0; i < MAX_TABLE; i++) {
    if (freqTable[i] > 0) {
      uint8_t symbol = i;
      uint16_t shortfreq = freqTable[symbol];
      memcpy(&combinString[SECTION_1 + SECTION_2 +
                           counter * (SECTION_3 + SECTION_4)],
             &symbol, sizeof(uint8_t));
      memcpy(&combinString[SECTION_1 + SECTION_2 +
                           counter * (SECTION_3 + SECTION_4) + 1],
             &shortfreq, sizeof(uint16_t));
      counter++;
    }
  }
  memcpy(&combinString[SECTION_1 + SECTION_2 +
                       freqTablelength * (SECTION_3 + SECTION_4)],
         &bitMatch, sizeof(uint8_t));
  printf("start copy encode\r\n");
  for (int j = 0; j < huffmanByteslength; j++) {
    uint8_t byte = 0;
    for (int i = 0; i < 8; i++) {
      if (j * 8 + i < encodeBitLength) {
        if (huffmanBytes[j * 8 + i] == '0')
          byte |= 0 << (7 - i);
        else if (huffmanBytes[j * 8 + i] == '1')
          byte |= 1 << (7 - i);
      }
    }
    printf("byte = 0x%02x\r\n", byte);
    memcpy(&combinString[SECTION_1 + SECTION_2 +
                         freqTablelength * (SECTION_3 + SECTION_4) + SECTION_5 +
                         j],
           &byte, 1);
  }
  return combinString;
}
uint8_t *compressProcess(uint8_t *data, int datasize, uint32_t *getCompreSize) {
  uint32_t freqTable[MAX_TABLE] = {0};
  initFreqTable(freqTable, data, datasize);
  // printFreqTable(freqTable);
  MinHeap *minheap = createHeap(MAX_TABLE);
  initMinHeap(minheap, freqTable);
  // printMinHeap(minheap);
  huffTreeNode *huffroot = plantHuffTree(minheap);
  // calculateTreeDepth(huffroot);
  printHuffTree(huffroot, 0);
  initCodeBook(CodeBook, MAX_TABLE);
  generateHuffTreecodebook(huffroot, CodeBook);
  printHuffCodeBook();
  verifyPrefixCodes(CodeBook);
  uint8_t *encodedata = getEncodeData(CodeBook, data, datasize, freqTable);
  uint32_t encodedataLen = getEncodeDataLen(CodeBook, freqTable);
  printf("encodedataLen = %d\r\n", encodedataLen);
  printf("encode = \r\n");
  for (int i = 0; i < encodedataLen; i++) {
    printf("%c", encodedata[i]);
  }
  printf("end\r\n");
  uint8_t *combinString = NULL;
  combinString = packageEncode(datasize, freqTable, encodedata, encodedataLen,
                               getCompreSize);
  freeHeap(minheap);
  freeHuffTree(huffroot);
  freeCodeBook(CodeBook, MAX_CODE);
  freeEncodeData(encodedata);
  return combinString;
}
void printHuffTree(huffTreeNode *node, int depth) {
  if (node == NULL) {
    return;
  }
  for (int i = 1; i < depth; i++) {
    printf("          %d", i); // 缩进来表示树的深度
  }
  printf("Byte: %u, Frequency: %u, IsLeaf: %d\n", node->byte, node->freq,
         node->isleaf);
  printHuffTree(node->left, depth + 1);
  printHuffTree(node->right, depth + 1);
}
int calculateTreeDepth(huffTreeNode *root) {
  if (root == NULL) {
    return 0; // 空树的深度为 0
  }
  if (root->isleaf) {
    return 1;
  }
  int leftDepth = calculateTreeDepth(root->left);
  int rightDepth = calculateTreeDepth(root->right);
  return (leftDepth > rightDepth ? leftDepth : rightDepth) + 1;
}
void printHuffCodeBook() {
  for (int i = 0; i < MAX_TABLE; i++) {
    if (CodeBook[i] != NULL) {
      printf("\nByte: %d, Code: %s\n", i, CodeBook[i]);
    }
  }
}
void printFreqTable(uint32_t *freqTable) {
  for (int i = 0; i < MAX_TABLE; i++) {
    if (freqTable[i] > 0) {
      printf("freqTable : byte = 0x%02x, freq = %d\r\n", i, freqTable[i]);
    }
  }
}

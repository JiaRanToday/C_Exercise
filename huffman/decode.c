#include "decode.h"
#include "encode.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#define SECTION_1 4
#define SECTION_2 2
#define SECTION_3 1
#define SECTION_4 2
#define SECTION_5 1
#define MAX_TABLE 256
static uint8_t *CodeBook[MAX_TABLE];
encodeForm *initencodeForm(uint8_t *recData) {
  if (recData == NULL) {
    printf("recData is empty");
    return NULL;
  }
  encodeForm *encodebuffer = (encodeForm *)malloc(sizeof(encodeForm));
  memset(encodebuffer, 0, sizeof(encodeForm));
  memcpy(&encodebuffer->orginalDatalength, recData, sizeof(uint32_t));
  memcpy(&encodebuffer->freqTablebytesCount, &recData[SECTION_1],
         sizeof(uint16_t));
  for (int i = 0; i < encodebuffer->freqTablebytesCount; i++) {
    uint8_t byte = recData[SECTION_1 + SECTION_2 + (SECTION_3 + SECTION_4) * i];
    uint32_t freq = 0;
    freq = (uint32_t)read_uint16_le(
        &recData[SECTION_1 + SECTION_2 + (SECTION_3 + SECTION_4) * i + 1], 0);
    encodebuffer->freqtable[byte] = freq;
    uint16_t array = read_uint16_le(
        &recData[SECTION_1 + SECTION_2 + (SECTION_3 + SECTION_4) * i + 1], 0);
  }
  memcpy(&encodebuffer->bitmatch,
         &recData[SECTION_1 + SECTION_2 +
                  (SECTION_3 + SECTION_4) * encodebuffer->freqTablebytesCount],
         1);
  encodebuffer->receivedData =
      &recData[SECTION_1 + SECTION_2 +
               (SECTION_3 + SECTION_4) * encodebuffer->freqTablebytesCount + 1];
  for (int i = 0; i < MAX_TABLE; i++) {
    if (encodebuffer->freqtable[i] > 0) {
      printf("freq[%d] = %u\r\n", i, encodebuffer->freqtable[i]);
    }
  }
  return encodebuffer;
}
void printfreqTable(uint16_t *freqtable) {
  for (int i = 0; i < MAX_TABLE; i++) {
    if (freqtable[i] > 0) {
      printf("freqtable: byte = 0x%02x , freq = %d\r\n", i, freqtable[i]);
    }
  }
}
void printcodeForm(encodeForm *encodebuffer) {
  printf("encodebuffer->orginalDatalength = %d\r\n",
         encodebuffer->orginalDatalength);
  printf("encodebuffer->freqTablebytesCount = %d\r\n",
         encodebuffer->freqTablebytesCount);
  printFreqTable(encodebuffer->freqtable);
  printf("bitmatch = %d\r\n", encodebuffer->bitmatch);
  for (int i = 0; i < 560; i++)
    printf("0x%02x ", encodebuffer->receivedData[i]);
}
void setBit(BitMap *map, int bitpos) {
  int index = bitpos / 8;
  uint8_t bit = bitpos % 8;
  map->bits[index] |= (1 << bit);
}
void clearbit(BitMap *map, int bitpos) {
  int index = bitpos / 8;
  uint8_t bit = bitpos % 8;
  map->bits[index] &= ~(1 << bit);
}
uint8_t getBit(const BitMap *map, int bitpos) {
  int index = bitpos / 8;
  uint8_t bit = bitpos % 8;
  // printf("bitpos = %d ,bit = %d\n", bitpos,
  // (map->bits[index] >> (7 - bit)) & 1);
  return (map->bits[index] >> (7 - bit)) & 1;
}
uint8_t *decodestart(huffTreeNode *huffroot, encodeForm *encodebuffer,
                     int huffdatalen) {
  BitMap *map = malloc(sizeof(BitMap));
  map->bits = encodebuffer->receivedData;
  map->size = huffdatalen;
  huffTreeNode *root = huffroot;
  uint8_t *decodeData = malloc(encodebuffer->orginalDatalength);
  memset(decodeData, 0, encodebuffer->orginalDatalength);
  int count = 0;
  printHuffTree(root, 0);
  for (int i = 0; i < map->size; i++) {
    if (count >= encodebuffer->orginalDatalength) {
      printf("Error: decoded data exceeds allocated buffer size.\n");
      break;
    }
    uint8_t bit = getBit(map, i);
    if (bit == 1) {
      root = root->right;
      if (root->isleaf == true) {
        printf("root->byte= 0x%x\r\n", root->byte);
        decodeData[count++] = root->byte;
        root = huffroot;
      }
    } else if (bit == 0) {
      root = root->left;
      if (root->isleaf == true) {
        printf("root->byte = 0x%x\r\n", root->byte);
        decodeData[count++] = root->byte;
        root = huffroot;
      }
    } else {
      printf("decode error\r\n");
      break;
    }
  }
  map->bits = NULL;
  free(map);
  return decodeData;
}
void printhuffCodeBook() {
  for (int i = 0; i < MAX_TABLE; i++) {
    if (CodeBook[i] != NULL) {
      printf("\nByte: %d, Code: %s\n", i, CodeBook[i]);
    }
  }
}
uint8_t *decompressProcess(uint8_t *recData) {
  encodeForm *encodebuffer = initencodeForm(recData);
  printcodeForm(encodebuffer);
  MinHeap *minheap = createHeap(MAX_TABLE);
  initMinHeap(minheap, encodebuffer->freqtable);
  printMinHeap(minheap);
  huffTreeNode *huffroot = plantHuffTree(minheap);
  verifyPrefixCodes(CodeBook);
  calculateTreeDepth(huffroot);
  printHuffTree(huffroot, 0);
  generateHuffTreecodebook(huffroot, CodeBook);
  printhuffCodeBook();
  int decodelen =
      getEncodeDataLen(CodeBook, (uint32_t *)encodebuffer->freqtable);
  printf("decodelen = %d\r\n", decodelen);
  printf("Original data size: %d\n", encodebuffer->orginalDatalength);
  uint8_t *decodeData = decodestart(huffroot, encodebuffer, decodelen);
  return decodeData;
}

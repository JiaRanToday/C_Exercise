#ifndef DECODE_H_
#define DECODE_H_
#include "encode.h"
typedef struct freqTable {
  uint8_t byte;
  uint16_t freq;
} freqTable;
typedef struct encodeForm {
  uint32_t orginalDatalength;
  uint16_t freqTablebytesCount;
  uint32_t freqtable[256];
  uint8_t bitmatch;
  uint8_t *receivedData;
} encodeForm;
typedef struct BitMap {
  uint8_t *bits;
  int size;
} BitMap;
// encodeForm *initencodeForm(uint8_t *recData);
// void printcodeForm(encodeForm *encodebuffer);
// uint8_t *decodestart(huffTreeNode *huffroot, encodeForm *encodebuffer,
                     // int huffdatalen);
// void printhuffCodeBook();
uint8_t *decompressProcess(uint8_t *recData);
// void setBit(BitMap *map, int bitpos);
// void clearbit(BitMap *map, int bitpos);
// uint8_t getBit(const BitMap *map, int bitpos);
#endif // !DECODE_H_

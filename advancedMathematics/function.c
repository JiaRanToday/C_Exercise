#include "function.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static mathFunction *function = NULL;

mathFunction *createFunction() {
  mathFunction *func = (mathFunction *)malloc(sizeof(mathFunction));
  if (func == NULL) {
    printf("createFunction malloc failed\r\n");
    return NULL;
  }
  return func;
}
void destoryFunction(mathFunction *func) {
  if (func->function_properties != NULL || func->independent_varible != NULL ||
      func->func != NULL) {
    printf("destoryFunction free failed\r\n");
    return;
  }
  free(func);
}

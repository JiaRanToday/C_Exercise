#include "function.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

mathFunction *func_1 = NULL;

mathFunction *createfunction(mathFunction *func) {
  func = (mathFunction *)malloc(sizeof(mathFunction));
  return func;
}
void destoryFunction(mathFunction *func) {
  if (func == NULL) {
    printf("func is NULL");
    return;
  }
  free(func);
}

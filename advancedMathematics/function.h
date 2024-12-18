#ifndef FUNCTION_H_
#define FUNCTION_H_
#include <stdbool.h>

typedef double *(FunctionImplementation)(void *independent_varible);

typedef struct mathFunction {
  void *independent_varible;
  FunctionImplementation func;
  void *function_properties;
} mathFunction;

#endif

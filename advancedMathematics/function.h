#ifndef FUNCTION_H_
#define FUNCTION_H_
#include <stdbool.h>
typedef struct {
  void *independent_varible;
  void *func(void *independent_varible);
};

#endif

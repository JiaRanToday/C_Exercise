#ifndef FUNCTION_H_
#define FUNCTION_H_
#include <stdbool.h>
typedef double *(FunctionImplementation)(void *independent_varible);
typedef struct mathFunction {
  void *independent_varible;
  FunctionImplementation func;
  void *function_properties;
} mathFunction;
typedef enum { SINGLEVARIBLE = 1, DOUBLEVARIBLE, THREEBLEVARIBLE } varibletype;
typedef struct {
  varibletype type;
  double x;
} single_varible;
typedef struct {
  varibletype type;
  double x;
  double y;
} double_varible;
typedef struct {
  varibletype type;
  double x;
  double y;
  double z;
} threeble_varible;
typedef struct {
  double demain_start;
  double demain_end;
} funcv1_properties;
#endif

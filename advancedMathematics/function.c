#include "function.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

mathFunction *function = NULL;

double func_v1(double x) { return 2; }
void initMathFunction() {
  function = createFunction();
  function->function_properties = NULL;
  func
}

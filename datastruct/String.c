#include <stdio.h>
#include <string.h>

typedef char Data;
Data *T;
typedef enum { ERROR = -1, FALSE, TRUE } State;
State StrAssign(Data *T, Data *chars) {
  if (chars == NULL) {
    return ERROR;
  }
}

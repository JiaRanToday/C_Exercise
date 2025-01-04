#include "Queue.h"
#include "Stack.h"
#include "perror.h"
#include <ctype.h>
typedef enum {
  DIGIT,
  OPERATOR_PRECEDENCE_1,
  OPERATOR_PRECEDENCE_2,
  LEFT_PARENTHESE,
  RIGHT_PARENTHESE,
  NOT_OPERATOR
} operatorType;
operatorType Distinguish_OperatorType(char operator) {
  if (isdigit(operator)) {
    return DIGIT;
  } else if (operator== '+' || operator== '-') {
    return OPERATOR_PRECEDENCE_2;
  } else if (operator== '*' || operator== '/') {
    return OPERATOR_PRECEDENCE_1;
  } else if (operator== '(') {
    return LEFT_PARENTHESE;
  } else if (operator== ')') {
    return RIGHT_PARENTHESE;
  } else {
    return NOT_OPERATOR;
  }
}
void InfixToPostfix(const char *infix, char *postfix) {
  SqStack stack;
  InitStack(&stack);
  char *pin = (char *)infix;
  int type = Distinguish_OperatorType(*pin);
  int index = 0;
  while (*pin != '\0') {
    switch (type) {
    case DIGIT:
      postfix[index++] = *pin;
      break;
    case OPERATOR_PRECEDENCE_1:
      Push(&stack, *pin);
      break;
    case OPERATOR_PRECEDENCE_2:
      if (stack.top != -1 ||)
        break;
    case LEFT_PARENTHESE:
      break;
    case RIGHT_PARENTHESE:
      break;
    case NOT_OPERATOR:
      break;
    }
  }
}

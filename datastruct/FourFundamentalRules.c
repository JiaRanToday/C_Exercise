#include "Queue.h"
#include "Stack.h"
#include <ctype.h>
#include <stdio.h>
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
  while (*pin++ != '\0') {
    switch (type) {
    case DIGIT:
      postfix[index++] = *pin;
      break;
    case OPERATOR_PRECEDENCE_1:
      Push(&stack, *pin);
      break;
    case OPERATOR_PRECEDENCE_2:
      if (!StackEmpty(&stack)) {
        SElemType e, temp;
        GetTop(&stack, &e);
        if (Distinguish_OperatorType(e) == OPERATOR_PRECEDENCE_1) {
          pop(&stack, &temp);
          postfix[index++] = temp;
          Push(&stack, *pin);
        } else {
          Push(&stack, *pin);
        }
      }
      break;
    case LEFT_PARENTHESE:
      Push(&stack, *pin);
      break;
    case RIGHT_PARENTHESE:
      SElemType e, temp;
      GetTop(&stack, &e);
      while (Distinguish_OperatorType(e) != LEFT_PARENTHESE) {
        pop(&stack, &temp);
        postfix[index++] = temp;
      }
      break;
    case NOT_OPERATOR:
      printf("not a operator ascii");
      break;
    }
  }
}

#include "evaluate.h"

#include <stdlib.h>

#include "../calculate/calculate.h"

double evaluateRPN(const Token* rpnTokens, int rpnCount, ErrorCode* err) {
  if (rpnTokens == NULL) return 0.0;
  if (err != NULL) *err = ERR_OK;
  double* numStack = malloc(rpnCount * sizeof(double));
  if (numStack == NULL) {
    if (err != NULL) *err = ERROR_MEMORY_ALLOCATION;
    return 0.0;
  }
  int top = -1;
  for (int i = 0; i < rpnCount; i++) {
    if (rpnTokens[i].type == TOKEN_NUMBER) {
      top++;
      numStack[top] = rpnTokens[i].data.number;
    } else if (rpnTokens[i].type == TOKEN_VARIABLE) {
      if (err != NULL) *err = ERROR_PARSER_MISSING_OPERAND;
      free(numStack);
      return 0.0;
    } else if (isOperator(rpnTokens[i].type)) {
      if (rpnTokens[i].type == TOKEN_UNAR_MINUS) {
        if (top < 0) {
          if (err != NULL) *err = ERROR_PARSER_MISSING_OPERAND;
          free(numStack);
          return 0.0;
        }
        numStack[top] = -numStack[top];
        continue;
      }
      if (top < 1) {
        if (err != NULL) *err = ERROR_PARSER_MISSING_OPERAND;
        free(numStack);
        return 0.0;
      }
      switch (rpnTokens[i].type) {
        case TOKEN_PLUS:
          numStack[top - 1] = CalculatePlus(numStack[top - 1], numStack[top]);
          top--;
          break;
        case TOKEN_MINUS:
          numStack[top - 1] = CalculateMinus(numStack[top - 1], numStack[top]);
          top--;
          break;
        case TOKEN_MULTIPLY:
          numStack[top - 1] =
              CalculateMultiply(numStack[top - 1], numStack[top]);
          top--;
          break;
        case TOKEN_DIVISION:
          numStack[top - 1] =
              CalculateDivision(numStack[top - 1], numStack[top]);
          top--;
          break;
        case TOKEN_NTHROOT_OPERATOR:
          numStack[top - 1] =
              CalculateNthRoot(numStack[top - 1], numStack[top]);
          top--;
          break;
        case TOKEN_POW_OPERATOR:
          numStack[top - 1] = CalculatePow(numStack[top - 1], numStack[top]);
          top--;
          break;
        default:
          break;
      }
    } else if (isFunction(rpnTokens[i].type)) {
      if (top < 0) {
        if (err != NULL) *err = ERROR_PARSER_MISSING_OPERAND;
        free(numStack);
        return 0.0;
      }
      switch (rpnTokens[i].type) {
        case TOKEN_COS:
          numStack[top] = CalculateCos(numStack[top]);
          break;
        case TOKEN_SIN:
          numStack[top] = CalculateSin(numStack[top]);
          break;
        case TOKEN_COT:
          numStack[top] = CalculateCot(numStack[top]);
          break;
        case TOKEN_TAN:
          numStack[top] = CalculateTan(numStack[top]);
          break;

        case TOKEN_ARCCOS:
          numStack[top] = CalculateArcCos(numStack[top]);
          break;
        case TOKEN_ARCSIN:
          numStack[top] = CalculateArcSin(numStack[top]);
          break;
        case TOKEN_ARCCOT:
          numStack[top] = CalculateArcCot(numStack[top]);
          break;
        case TOKEN_ARCTAN:
          numStack[top] = CalculateArcTan(numStack[top]);
          break;

        case TOKEN_NTHROOT_FUNCTION:
          if (top < 1) {
            if (err != NULL) *err = ERROR_PARSER_MISSING_OPERAND;
            free(numStack);
            return 0.0;
          }
          numStack[top - 1] =
              CalculateNthRoot(numStack[top - 1], numStack[top]);
          top--;
          break;
        case TOKEN_POW_FUNCTION:
          if (top < 1) {
            if (err != NULL) *err = ERROR_PARSER_MISSING_OPERAND;
            free(numStack);
            return 0.0;
          }
          numStack[top - 1] = CalculatePow(numStack[top - 1], numStack[top]);
          top--;
          break;
        default:
          break;
      }
      continue;
    }
  }
  if (top != 0) {
    if (err != NULL) *err = ERROR_PARSER_MISSING_OPERAND;
    free(numStack);
    return 0.0;
  }
  double result = numStack[top];
  free(numStack);
  return result;
}
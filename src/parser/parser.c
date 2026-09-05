#include "parser.h"

#include <stdbool.h>
#include <stdlib.h>

#include "stack.h"

bool isOperator(TypeToken type);
bool isFunction(TypeToken type);
bool isVariable(TypeToken type);
bool isRightAssociative(TypeToken type);

static TokenProperties tokenProps[] = {
    [TOKEN_PLUS] = {.precedence = 2,
                    .isAssociative = false,
                    .isOperator = true},
    [TOKEN_MINUS] = {.precedence = 2,
                     .isAssociative = false,
                     .isOperator = true},
    [TOKEN_UNAR_MINUS] = {.precedence = 4,
                          .isAssociative = true,
                          .isOperator = true},
    [TOKEN_MULTIPLY] = {.precedence = 3,
                        .isAssociative = false,
                        .isOperator = true},
    [TOKEN_DIVISION] = {.precedence = 3,
                        .isAssociative = false,
                        .isOperator = true},
    [TOKEN_POW_OPERATOR] = {.precedence = 4,
                            .isAssociative = true,
                            .isOperator = true},
    [TOKEN_NTHROOT_OPERATOR] = {.precedence = 4,
                                .isAssociative = true,
                                .isOperator = true},
// *function
#define X(str, enum_type) \
  [enum_type] = {.precedence = 5, .isAssociative = true, .isFunction = true},
    FUNCTION_LIST
#undef X
};

int totalTokens = sizeof(tokenProps) / sizeof(tokenProps[0]);

bool parserToRPN(const Context* inCtx, Context* outCtx) {
  int i = 0;
  Token topToken;
  TokenStack opStack;
  outCtx->count = 0;
  outCtx->capacity = START_SIZE;
  outCtx->tokens = malloc(outCtx->capacity * sizeof(Token));
  if (!outCtx->tokens) return false;
  if (stackInit(&opStack, inCtx->count) != STACK_OK) {
    freeTokens(outCtx);
    return false;
  }
  while (i < inCtx->count) {
    Token currentToken = inCtx->tokens[i];
    switch (currentToken.token) {
      case TOKEN_NUMBER:
      case TOKEN_VARIABLE:
        outCtx->tokens[outCtx->count++] = currentToken;
        break;
      case TOKEN_OPEN_PAREN:
        stackPush(&opStack, currentToken);
        break;
#define X(str, enum_type) case enum_type:
        FUNCTION_LIST
#undef X
        stackPush(&opStack, currentToken);
        break;
      case TOKEN_CLOSE_PAREN:
        while (!stackIsEmpty(&opStack) &&
               stackPeek(&opStack, &topToken) == STACK_OK &&
               topToken.token != TOKEN_OPEN_PAREN) {
          stackPop(&opStack, &topToken);
          outCtx->tokens[outCtx->count++] = topToken;
        }
        if (stackIsEmpty(&opStack)) {
          stackFree(&opStack);
          freeTokens(outCtx);
          return false;
        }
        stackPop(&opStack, &topToken);
        if (!stackIsEmpty(&opStack) &&
            stackPeek(&opStack, &topToken) == STACK_OK &&
            isFunction(topToken.token)) {
          stackPop(&opStack, &topToken);
          outCtx->tokens[outCtx->count++] = topToken;
        }
        break;
      case TOKEN_PLUS:
      case TOKEN_MINUS:
      case TOKEN_MULTIPLY:
      case TOKEN_DIVISION:
      case TOKEN_POW_OPERATOR:
      case TOKEN_UNAR_MINUS:
      case TOKEN_NTHROOT_OPERATOR:
        while (!stackIsEmpty(&opStack) &&
               stackPeek(&opStack, &topToken) == STACK_OK &&
               (isOperator(topToken.token) || isFunction(topToken.token)) &&
               ((!isRightAssociative(currentToken.token) &&
                 tokenProps[topToken.token].precedence >=
                     tokenProps[currentToken.token].precedence) ||
                (isRightAssociative(currentToken.token) &&
                 tokenProps[topToken.token].precedence >
                     tokenProps[currentToken.token].precedence))) {
          stackPop(&opStack, &topToken);
          outCtx->tokens[outCtx->count++] = topToken;
        }
        stackPush(&opStack, currentToken);
        break;
      default:
        stackFree(&opStack);
        freeTokens(outCtx);
        return false;
    }
    i++;
  }
  while (!stackIsEmpty(&opStack)) {
    stackPop(&opStack, &topToken);
    if (topToken.token == TOKEN_OPEN_PAREN) {
      stackFree(&opStack);
      freeTokens(outCtx);
      return false;
    }
    outCtx->tokens[outCtx->count++] = topToken;
  }
  stackFree(&opStack);
  return true;
}

bool isOperator(TypeToken type) {
  if (type < 0 ||
      type >= (TypeToken)(sizeof(tokenProps) / sizeof(tokenProps[0])))
    return false;
  return tokenProps[type].isOperator;
}

bool isFunction(TypeToken type) {
  if (type < 0 ||
      type >= (TypeToken)(sizeof(tokenProps) / sizeof(tokenProps[0])))
    return false;
  return tokenProps[type].isFunction;
}

bool isRightAssociative(TypeToken type) {
  if (type < 0 ||
      type >= (TypeToken)(sizeof(tokenProps) / sizeof(tokenProps[0])))
    return false;
  return tokenProps[type].isAssociative;
}

bool isOperand(TypeToken type) {
  if (type < 0 ||
      type >= (TypeToken)(sizeof(tokenProps) / sizeof(tokenProps[0])))
    return false;
  return (type == TOKEN_NUMBER || type == TOKEN_VARIABLE);
}

void freeTokens(Context* context) {
  if (context && context->tokens) {
    free(context->tokens);
    context->tokens = NULL;
  }
}
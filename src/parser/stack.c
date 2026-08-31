#include "stack.h"

#include <assert.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>

#include "parser.h"

StackStatus stackInit(TokenStack* stack, int intCapacity) {
  if (intCapacity <= 0 || stack == NULL) return STACK_ERROR_NULL;
  stack->items = malloc(intCapacity * sizeof(Token));
  stack->top = -1;
  if (stack->items == NULL) {
    stack->capacity = 0;
    return STACK_ERROR_NO_MEMORY;
  }
  stack->capacity = intCapacity;
  return STACK_OK;
}

StackStatus stackPush(TokenStack* stack, Token token) {
  if (stack == NULL) return STACK_ERROR_NULL;
  if (stack->items == NULL) return STACK_ERROR_NULL;
  if (stack->capacity <= 0) return STACK_ERROR_NULL;
  if (stack->top + 1 >= stack->capacity) {
    int newCapacity = stack->capacity * 2;
    Token* newItems = realloc(stack->items, newCapacity * sizeof(Token));
    if (newItems == NULL) return STACK_ERROR_NO_MEMORY;
    stack->items = newItems;
    stack->capacity = newCapacity;
  }
  stack->top++;
  stack->items[stack->top] = token;
  return STACK_OK;
}

StackStatus stackPop(TokenStack* stack, Token* outToken) {
  if (stack == NULL) return STACK_ERROR_NULL;
  if (outToken == NULL) return STACK_ERROR_NULL;
  if (stack->items == NULL) return STACK_ERROR_NULL;
  if (stack->capacity <= 0) return STACK_ERROR_NULL;
  if (stack->top < 0) return STACK_ERROR_UNDERFLOW;
  *outToken = stack->items[stack->top];
  stack->top--;
  return STACK_OK;
}

StackStatus stackPeek(const TokenStack* stack, Token* outToken) {
  if (stack == NULL) return STACK_ERROR_NULL;
  if (outToken == NULL) return STACK_ERROR_NULL;
  if (stack->items == NULL) return STACK_ERROR_NULL;
  if (stack->capacity <= 0) return STACK_ERROR_NULL;
  if (stack->top < 0) return STACK_ERROR_UNDERFLOW;
  *outToken = stack->items[stack->top];
  return STACK_OK;
}

bool stackIsEmpty(const TokenStack* stack) {
  if (stack == NULL) return true;
  if (stack->items == NULL || stack->capacity <= 0) return true;
  if (stack->top < 0) return true;
  return false;
}

StackStatus stackFree(TokenStack* stack) {
  if (stack == NULL) return STACK_ERROR_NULL;
  if (stack->items != NULL) {
    free(stack->items);
    stack->items = NULL;
  }
  stack->top = -1;
  stack->capacity = 0;
  return STACK_OK;
}
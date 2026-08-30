#ifndef STACK_H
#define STACK_H

#include "parser.h"


typedef struct {
    Token *items;
    int capacity;
    int top;
} TokenStack;


typedef enum {
    STACK_OK = 0,
    STACK_ERROR_NULL,
    STACK_ERROR_OVERFLOW,
    STACK_ERROR_UNDERFLOW,
    STACK_ERROR_NO_MEMORY
} StackStatus;


/* Prototype stack operations*/
StackStatus stackInit(TokenStack *stack, int capacity);
StackStatus stackPush(TokenStack *stack, Token token);
StackStatus stackPop(TokenStack *stack, Token *outToken);
StackStatus stackPeek(const TokenStack *stack, Token *outToken);
bool stackIsEmpty(const TokenStack *stack);
StackStatus stackFree(TokenStack *stack);

#endif
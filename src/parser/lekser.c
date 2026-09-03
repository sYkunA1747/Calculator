#include "parser.h"
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

static TypeToken getOperatorFunctionType(char ch);
static bool tokenizeSpace(Context *context);
static bool tokenizeVariable(Context *context);
static bool tokenizeOperator(Context *context);
static bool tokenizeFunction(Context *context);
static bool tokenizeError(Context *context);
static TypeToken parseFunctionName(const char *name);
static bool lekserRealloc(Context *context);
static States determineNextState(Context *ctx);

Token *tokenize(const char *expr, int *tokenCount){
    Context ctx;
    ctx.str = expr;
    ctx.index = 0;
    ctx.count = 0;
    ctx.capacity = START_SIZE;
    ctx.type = STATE_ERROR_HANDLING;
    ctx.tokens = malloc(START_SIZE*sizeof(Token));
    while(ctx.str[ctx.index] != '\0'){
        if(ctx.capacity <= ctx.count+1 && !lekserRealloc(&ctx)){
            freeTokens(&ctx);
            return NULL;
         }
        ctx.type = determineNextState(&ctx);
        if(!dispatchState(&ctx)){
            ctx.count = 0;
            *tokenCount = 0;
            freeTokens(&ctx);
            return NULL;
        }
    }
    *tokenCount = ctx.count;
    return ctx.tokens;
}

static bool tokenizeSpace(Context *context){
    context->index++;
    return true;
}

static bool tokenizeVariable(Context *context){
    int count = context->count;
    char *endPtr;
    context->tokens[count].number = strtod(&context->str[context->index], &endPtr);
    if(endPtr == &context->str[context->index]) return false;
    context->tokens[count].token = TOKEN_NUMBER;
    context->index += (endPtr - &context->str[context->index]);
    context->count++;
    return true;
}

static bool tokenizeOperator(Context *context){
    TypeToken type = getOperatorFunctionType(context->str[context->index]);
    context->tokens[context->count].token = type;
    context->index++;
    context->count++;
    return true;
}

static TypeToken parseFunctionName(const char *name){
    #define X(str, enum_type) if (strcmp(name, str) == 0) return enum_type;
        FUNCTION_LIST
    #undef X
    return TOKEN_UNKNOWN;
}

static bool tokenizeFunction(Context *context){
    int len = 0;
    char buffer[MAX_TOKEN_LEN];
    while(isalpha((unsigned char)context->str[context->index]) && len < MAX_TOKEN_LEN - 1){
        buffer[len] = tolower((unsigned char)context->str[context->index]);
        context->index++;
        len++;
    }
    buffer[len] = '\0';
    TypeToken type = parseFunctionName(buffer);
    if(type == TOKEN_UNKNOWN) return false;
    context->tokens[context->count].token = type;
    context->count++;
    return true;
}
   
static bool tokenizeError(Context *context){
    return false;
}


bool dispatchState(Context *context){
    switch(context->type){
        case STATE_SPACE_HANDLING:      return tokenizeSpace(context);
        case STATE_VARIABLE_HANDLING:   return tokenizeVariable(context);
        case STATE_OPERATOR_HANDLING:   return tokenizeOperator(context);  
        case STATE_FUNCTION_HANDLING:   return tokenizeFunction(context); 
        case STATE_ERROR_HANDLING:      return tokenizeError(context); 
        default: return false;
    }
}


static TypeToken getOperatorFunctionType(char ch) {
  switch (ch) {
    case '+':
      return TOKEN_PLUS;
    case '-':
      return TOKEN_MINUS;
    case '*':
      return TOKEN_MULTIPLY;
    case '/':
      return TOKEN_DIVISION;
    case '^':
      return TOKEN_POW_OPERATOR;
    case '_':
      return TOKEN_UNAR_MINUS;
    case '~':
      return TOKEN_NTHROOT_OPERATOR;
    case '(':
      return TOKEN_OPEN_PAREN;
    case ')':
      return TOKEN_CLOSE_PAREN;
    default:
      return TOKEN_UNKNOWN;
  }
}

static bool lekserRealloc(Context *context){
    int newCapacity = context->capacity*2;
    Token *newTokens = realloc(context->tokens, newCapacity*sizeof(Token));
    if(newTokens == NULL){
        context->tokens = NULL;
        return false;
    }
    context->tokens = newTokens;
    context->capacity = newCapacity;
    return true;
}

static States determineNextState(Context *ctx){
    return (isspace((unsigned char)ctx->str[ctx->index])) ? STATE_SPACE_HANDLING :
            ((isdigit((unsigned char)ctx->str[ctx->index]) || ctx->str[ctx->index] == '.')) ? STATE_VARIABLE_HANDLING :
                (getOperatorFunctionType(ctx->str[ctx->index]) != TOKEN_UNKNOWN) ? STATE_OPERATOR_HANDLING :
                    (isalpha((unsigned char)ctx->str[ctx->index])) ? STATE_FUNCTION_HANDLING :
                        STATE_ERROR_HANDLING;
}
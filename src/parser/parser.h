#ifndef PARSER_H
#define PARSER_H

#include <stdbool.h>

#define MAX_TOKEN_LEN 32

#define PRIORITY_PLUS_MINUS 1
#define PRIORITY_MULTIPLY_DIVISION 2
#define PRIORITY_POW_NTHROOT 3
#define PRIORITY_UNAR_MINUS 4
#define PRIORITY_UNKNOWN 0

#ifndef FUNCTION_LIST
#define FUNCTION_LIST \
    X("sin", TOKEN_SIN)\
    X("cos", TOKEN_COS)\
    X("tan", TOKEN_TAN)\
    X("cot", TOKEN_COT)\
    X("arcsin", TOKEN_ARCSIN)\
    X("arccos", TOKEN_ARCCOS)\
    X("arctan", TOKEN_ARCTAN)\
    X("arccotan", TOKEN_ARCCOT)\
    X("mypow", TOKEN_POW_FUNCTION)\
    X("nthroot", TOKEN_NTHROOT_FUNCTION) 
#endif

typedef enum{
    //number
    TOKEN_NUMBER,

    //Operator
    TOKEN_PLUS,
    TOKEN_UNAR_MINUS,
    TOKEN_MINUS,
    TOKEN_MULTIPLY,
    TOKEN_DIVISION,
    TOKEN_POW_OPERATOR,
    TOKEN_NTHROOT_OPERATOR,
    //fucntions

    #define  X(str, enum_type) enum_type,
    FUNCTION_LIST
    #undef X
    
    
    // Variable
    TOKEN_VARIABLE,
    
    //Parens
    TOKEN_OPEN_PAREN,
    TOKEN_CLOSE_PAREN,

   
    //Special Tokens
    TOKEN_UNKNOWN,
    TOKEN_EOF
}TokenType;


typedef struct {
    TokenType type;
    union{
        double number;
        char name[MAX_TOKEN_LEN];
        int priority;
    }data;
} Token;


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

bool isOperator(TokenType type);
bool isBinaryOperator(TokenType type);
bool isFunction(TokenType type);
bool isVariable(TokenType type);
bool isParen(TokenType type);

int getOperatorPriority(TokenType type);

Token *tokenize(const char *expr, int *token_count);
void freeTokens(Token *tokens, int count);


/* Prototype stack operations*/
StackStatus stackInit(TokenStack *stack, int capacity);
StackStatus stackPush(TokenStack *stack, Token token);
StackStatus stackPop(TokenStack *stack, Token *outToken);
StackStatus stackPeek(const TokenStack *stack, Token *outToken);
bool stackIsEmpty(const TokenStack *stack);
StackStatus stackFree(TokenStack *stack);


TokenType getFunction(const char *name);
TokenType getOperatorFunctionType(char ch);

#endif
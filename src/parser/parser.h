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



bool isOperator(TokenType type);
bool isBinaryOperator(TokenType type);
bool isFunction(TokenType type);
bool isVariable(TokenType type);
bool isParen(TokenType type);

int getOperatorPriority(TokenType type);

Token *tokenize(const char *expr, int *token_count);
void freeTokens(Token *tokens);



TokenType getFunction(const char *name);
TokenType getOperatorFunctionType(char ch);

#endif
#include "parser.h"

#include <assert.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>


Token *tokenize(const char *expr, int *tokenCount){
    if(expr == NULL || tokenCount == NULL) return NULL;
    int i = 0, capacity = 10, index = 0;
    Token *tokens = malloc(capacity*(sizeof(Token)));
    if(tokens == NULL) return NULL;

    while(expr[i]!='\0'){
        if(index >= capacity){
            capacity*=2;
            Token *temp = realloc(tokens, capacity*sizeof(Token));
            if(temp == NULL) {
                free(tokens);
                return NULL;
            }
            tokens = temp;
        }


        if(isspace((unsigned char)expr[i])){
            i++;
            continue;
        } else if(isdigit((unsigned char)expr[i]) || expr[i] == '.'){
            char*end;
            tokens[index].type = TOKEN_NUMBER;
            tokens[index].data.number = strtod(&expr[i], &end);
            if(end == &expr[i]){
                tokens[index].type = TOKEN_UNKNOWN;
                i++;
                index++;
                continue;
            }
            index++;
            i = end - expr;
            continue;
        } else if(isalpha((unsigned char)expr[i])){
            int startIndex = i; 
            while(expr[i] != '\0' && isalpha((unsigned char)expr[i])){
                i++;
            }
            int len = i - startIndex;
            if(len >= MAX_TOKEN_LEN) len = MAX_TOKEN_LEN - 1;
            for(int j = 0; j < len; j++)
                tokens[index].data.name[j] = tolower((unsigned char)expr[startIndex+j]);
            tokens[index].data.name[len] = '\0';
        
            tokens[index].type =  getFunction(tokens[index].data.name);
            index++;
            continue;
        }  else if(getOperatorFunctionType(expr[i]) != TOKEN_UNKNOWN){
            TokenType openType = getOperatorFunctionType(expr[i]); 
            if(openType == TOKEN_MINUS){
                if(index == 0 || isOperator(tokens[index-1].type) || tokens[index-1].type == TOKEN_OPEN_PAREN)
                    openType = TOKEN_UNAR_MINUS;
            }
            tokens[index].type = openType;
            index++;
            i++;
            continue;
        } else {
            tokens[index].type = TOKEN_UNKNOWN;
            index++;
            i++;
        }
    }

    *tokenCount = index;
    return tokens;
}


TokenType getFunction(const char *name){
    #define X(str, enum_type)if(strcmp(name,str) == 0) return enum_type;
    FUNCTION_LIST
    #undef X

    return TOKEN_VARIABLE;
}


TokenType getOperatorFunctionType(char ch){
    switch(ch){
        case'+': return TOKEN_PLUS; 
        case'-': return TOKEN_MINUS;
        case'*': return TOKEN_MULTIPLY;
        case'/': return TOKEN_DIVISION;
        case'^': return TOKEN_POW_OPERATOR;
        case'_': return TOKEN_UNAR_MINUS;
        case'~': return TOKEN_NTHROOT_OPERATOR;
        case'(': return TOKEN_OPEN_PAREN;
        case')': return TOKEN_CLOSE_PAREN;
        default: return TOKEN_UNKNOWN;
    }
}


void freeTokens(Token *tokens){
    assert(tokens != NULL);
    free(tokens);
}


bool isOperator(TokenType type){
    return(isBinaryOperator(type) || type == TOKEN_UNAR_MINUS);
}


bool isBinaryOperator(TokenType type){
    switch(type){
        case TOKEN_PLUS: return true;
        case TOKEN_MINUS: return true;
        case TOKEN_MULTIPLY: return true;
        case TOKEN_DIVISION: return true;
        case TOKEN_POW_OPERATOR: return true;
        case TOKEN_NTHROOT_OPERATOR: return true;
        default: return false;
    }
}


bool isFunction(TokenType type){
    return (type >= TOKEN_SIN && type <= TOKEN_NTHROOT_FUNCTION);
}


bool isVariable(TokenType type){
    return(type == TOKEN_VARIABLE);
}


bool isParen(TokenType type){
    return (type == TOKEN_OPEN_PAREN || type == TOKEN_CLOSE_PAREN);
    
}

int getOperatorPriority(TokenType type){
    switch(type){
        case TOKEN_PLUS:
        case TOKEN_MINUS:
            return PRIORITY_PLUS_MINUS;
        case TOKEN_DIVISION:
        case TOKEN_MULTIPLY:
            return PRIORITY_MULTIPLY_DIVISION;
        case TOKEN_POW_OPERATOR:
        case TOKEN_NTHROOT_OPERATOR:
            return PRIORITY_POW_NTHROOT;
        case TOKEN_UNAR_MINUS: 
            return PRIORITY_UNAR_MINUS;
        default: 
            return PRIORITY_UNKNOWN;
    }
}


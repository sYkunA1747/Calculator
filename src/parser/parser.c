#include "parser.h"
#include "stack.h"

#include <stdlib.h>

Token *parserToRPN(const Token *inTokens, int inCount, int *outCount, ErrorCode *err) {
    if(inTokens == NULL || outCount == NULL) return NULL;
    if(err != NULL) *err = ERR_OK;
    TokenStack opStack;
    StackStatus status = stackInit(&opStack, inCount);
    if(status != STACK_OK){
        if(err != NULL) *err = ERROR_MEMORY_ALLOCATION;
            return NULL;
    }
    Token *output = malloc(inCount*(sizeof(Token)));
    if(output == NULL) {
        if(err != NULL) *err = ERROR_MEMORY_ALLOCATION;
        stackFree(&opStack);
        return NULL;
    }
    int outIndex = 0;
    for(int i = 0; i < inCount; i++){
        if(isVariable(inTokens[i].type) || inTokens[i].type == TOKEN_NUMBER){
            output[outIndex] = inTokens[i];
            outIndex++;
            continue;
        } else if(inTokens[i].type == TOKEN_OPEN_PAREN){
            if(stackPush(&opStack, inTokens[i]) != STACK_OK){
                if(err != NULL) *err = ERROR_MEMORY_ALLOCATION;
                free(output);
                stackFree(&opStack);
                return NULL;
            }
            continue;
        } else if(isFunction(inTokens[i].type)){
            if(stackPush(&opStack, inTokens[i]) != STACK_OK){
                if(err != NULL) *err = ERROR_MEMORY_ALLOCATION;
                free(output);
                stackFree(&opStack);
                return NULL;
            }
            continue;
        } else if(isOperator(inTokens[i].type)){
            Token topToken;
            while(!stackIsEmpty(&opStack) && stackPeek(&opStack,&topToken) == STACK_OK ){
                int topPri = getOperatorPriority(topToken.type);
                int currPri = getOperatorPriority(inTokens[i].type);

                if(topPri > currPri || (topPri == currPri && !isRightAssociative(inTokens[i].type))){            
                    stackPop(&opStack, &topToken);
                    output[outIndex] =  topToken;
                    outIndex++;
                } else {
                    break;
                }
            }
            if(stackPush(&opStack, inTokens[i]) != STACK_OK){
                if(err != NULL) *err = ERROR_MEMORY_ALLOCATION;
                free(output);
                stackFree(&opStack);
                return NULL;
            }
            continue;
        } else if(inTokens[i].type == TOKEN_CLOSE_PAREN){
            Token topToken;
            while(!stackIsEmpty(&opStack) && stackPeek(&opStack, &topToken) == STACK_OK){
                if(topToken.type != TOKEN_OPEN_PAREN){
                    stackPop(&opStack, &topToken);
                    output[outIndex] = topToken;
                    outIndex++;
                } else {
                    break;
                }
            }
            if(stackPop(&opStack, &topToken) != STACK_OK || topToken.type != TOKEN_OPEN_PAREN){
                if(err != NULL) *err = ERROR_PARSER_CLOSE_PAREN_UNBALANCED;
                free(output);
                stackFree(&opStack);
                return NULL;
            }
            if(!stackIsEmpty(&opStack) && stackPeek(&opStack, &topToken) == STACK_OK){
                if(isFunction(topToken.type)){    
                    stackPop(&opStack, &topToken);
                    output[outIndex] = topToken;
                    outIndex++;
                }
            }
            continue;
        }
    }

    while(!stackIsEmpty(&opStack)){
        Token topToken;
        stackPop(&opStack, &topToken);

        if(topToken.type == TOKEN_OPEN_PAREN){
            if(err != NULL) *err = ERROR_PARSER_OPEN_PAREN_UNBALANCED;
            free(output);
            stackFree(&opStack);
            return NULL;
        }
        output[outIndex] = topToken;
        outIndex++;
    }

    if(err != NULL)
        *err = ERR_OK;

    *outCount = outIndex;
    stackFree(&opStack);
    return output;
}






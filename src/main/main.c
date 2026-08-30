#include "../parser/parser.h"
#include "../evaluate/evaluate.h"
#include "../errorhandling/errors.h"
#include "../errorhandling/errorCode.h"
#include <stdio.h>

int main(){
    const char *expr = "3 + Sin(-0)";
    int rpnCount = 0, tokenCount = 0;
    ErrorCode err = ERR_OK;
    Token *tokens = tokenize(expr, &tokenCount);
    if (tokens == NULL){
    logError(ERROR_MEMORY_ALLOCATION, "Лексический анализ");
        return 1;   
    }
    Token *rpnTokens = parserToRPN(tokens, tokenCount, &rpnCount, &err);
    if(rpnTokens == NULL){
        freeTokens(tokens);
        return -1;
    }
    double result = evaluateRPN(rpnTokens, rpnCount, &err);
    if(err != ERR_OK){
        logError(err, "Вычислитель ОПЗ");
        freeTokens(tokens);
        freeTokens(rpnTokens);
        return -1;
    }
    printf("Результат: %f\n", result);
    freeTokens(tokens);
    freeTokens(rpnTokens);
    return 0;
}
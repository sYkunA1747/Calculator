#include "../src/parser/parser.h"
#include "../src/evaluate/evaluate.h"
#include "../src/errorhandling/errors.h"
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) {
    if (Size == 0 || Size > 256) {
        return 0; 
    }
    char *expr = malloc(Size + 1);
    if (expr == NULL) {
        return 0; 
    }
    memcpy(expr, Data, Size);
    expr[Size] = '\0';
    int tokenCount = 0;
    int rpnCount = 0;
    ErrorCode err = ERR_OK;
    Token *tokens = tokenize(expr, &tokenCount);
    if (tokens != NULL) {
        Token *rpnTokens = parserToRPN(tokens, tokenCount, &rpnCount, &err);
        if (rpnTokens != NULL) {
            evaluateRPN(rpnTokens, rpnCount, &err);
            freeTokens(rpnTokens);
        }
        freeTokens(tokens);
    }
    free(expr);
    return 0; 
}

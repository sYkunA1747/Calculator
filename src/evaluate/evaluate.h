#ifndef EVALUATE_H
#define EVALUATE_H

#include "../errorhandling/errors.h"
#include "../parser/parser.h"

double evaluateRPN(const Token *rpnTokens, int rpnCount, ErrorCode *err);


#endif
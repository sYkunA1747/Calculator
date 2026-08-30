#include "testFunction.h"
#include "../src/parser/parser.h"
#include <stdio.h>
#include <stdbool.h>



bool TestParseOneStr(void){
    return ASSERT_STR_EQ("2*A + 2*C - A*B", "2*a+2*c-a*b");
}

bool TestParseTwoStr(void){
    return ASSERT_STR_EQ("tan(2A) - pow(A,2)", "tg(2*a)-pow(a,2)");
}

bool TestParseThreeStr(void){
    return ASSERT_STR_EQ("cos(2*A) + 2^C - nthroot(2)", "cos(2*a)+2^c-sqr(2)");
}


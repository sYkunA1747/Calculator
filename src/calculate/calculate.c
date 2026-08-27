#include "calculate.h"

#include <math.h>
#include <limits.h>

static double intPow(double base, int exp);
static double myPow(double numOne, double numTwo);
double NthRoot(double base, double exp);

double CalculatePlus(double numOne, double numTwo){
    return numOne+numTwo;
}


double CalculateMinus(double numOne, double numTwo){
    return numOne-numTwo;
}


double CalculateMultiply(double numOne, double numTwo){
    return numOne*numTwo;
}


double CalculateDivision(double numOne, double numTwo){
    if(numTwo == 0.0) return INFINITY;
    return numOne/numTwo;
}


double CalculateNthRoot(double numOne, double numTwo){
    return NthRoot(numOne,numTwo);
}


double CalculatePow(double numOne, double numTwo){
    return myPow(numOne, numTwo);
}


double NthRoot(double base, double exp){
    if(exp == 0.0) return INFINITY;

    return myPow(base, 1.0/exp);
}


/*============================================*/
/*             Additional                     */
/*                Function                    */
/*============================================*/

static double intPow(double base, int exp) {
    if (exp == 0) return 1.0;
    
    long long longExp = exp;

    if (exp < 0) {
        base = 1.0 / base;
        longExp = - longExp;
    }
    double result = 1.0;
    do {
       if(longExp % 2 == 1) result *= base;
       base *= base;
       longExp /= 2;
    } while(longExp > 0);

    return result;
}


static double myPow(double numOne, double numTwo){
    if(numOne == 0.0 && numTwo == 0.0) return 1.0;

    if(numOne == 0.0 && numTwo < 0.0) return INFINITY;

    if(numTwo < INT_MIN || numTwo > INT_MAX){
        if(numOne > 0.0) return exp(numTwo * log(numOne));
        return NAN;
    }
    
    if(numOne < 0.0 && numTwo != (int)numTwo) return NAN;

    if(numTwo == (int)numTwo)
        return intPow(numOne, (int)numTwo);

    if(numOne > 0.0)
        return exp(numTwo * log(numOne));

    return NAN;
}


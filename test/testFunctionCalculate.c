#include "testFunction.h"
//#include "FunctionCalculate.h" // Пока не реализован ./src

#include <stdbool.h>
#include <math.h>


bool TestCalculatePlus(double numOne, double numTwo){
    return ASSERT_TEST(CalculatePlus(numOne,numTwo), numOne+numTwo);
}


bool TestCalculateMinus(double numOne, double numTwo){
    return ASSERT_TEST(CalculateMinus(numOne,numTwo), numOne-numTwo);
}


bool TestCalculateMultiply(double numOne, double numTwo){
    return ASSERT_TEST(CalculateMultiply(numOne, numTwo), numOne*numTwo);
}


bool TestCalculateDivision(double numOne, double numTwo){
    if(numTwo == 0.0)
        return false;
    return ASSERT_TEST(CalculateDivision(numOne,numTwo), numOne/numTwo);
}


bool TestCalculateNthRoot(double number, double degree){
    if(degree == 0.0)
        return false;
    return ASSERT_TEST(CalculateNthRoot(number,degree), pow(number, 1.0/degree)); 
}   


bool TestCalculatePow(double numOne, double numTwo){
    return ASSERT_TEST(CalculatePow(numOne, numTwo), pow(numOne,numTwo));
}




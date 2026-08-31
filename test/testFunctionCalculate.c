#include <math.h>
#include <stdbool.h>

#include "../src/calculate/calculate.h"
#include "testFunction.h"

static bool TestCalculatePlus(const TestCase* self, double actualResult) {
  return ASSERT_TEST(actualResult, self->expected);
}

static bool TestCalculateMinus(const TestCase* self, double actualResult) {
  return ASSERT_TEST(actualResult, self->expected);
}

static bool TestCalculateMultiply(const TestCase* self, double actualResult) {
  return ASSERT_TEST(actualResult, self->expected);
}

static bool TestCalculateDivision(const TestCase* self, double actualResult) {
  return ASSERT_TEST(actualResult, self->expected);
}

static bool TestCalculatePow(const TestCase* self, double actualResult) {
  return ASSERT_TEST(actualResult, self->expected);
}

static bool TestCalculateNthRoot(const TestCase* self, double actualResult) {
  return ASSERT_TEST(actualResult, self->expected);
}

static bool TestCalculateDivisionByZero(const TestCase* self,
                                        double actualResult) {
  (void)self;
  return isinf(actualResult) || isnan(actualResult);
}

static const TestCase calculateTests[] = {
    {"Plus_Basic", "2+2", TestCalculatePlus, 2.0, 2.0, 4.0},
    {"Plus_Neg_Left", "-5+10", TestCalculatePlus, -5.0, 10.0, 5.0},
    {"Plus_Neg_Right", "5+-10", TestCalculatePlus, 5.0, -10.0, -5.0},
    {"Plus_Both_Neg", "-5+-5", TestCalculatePlus, -5.0, -5.0, -10.0},
    {"Plus_Zeros", "0+0", TestCalculatePlus, 0.0, 0.0, 0.0},
    {"Plus_Neg_Zero", "0+-0", TestCalculatePlus, 0.0, -0.0, 0.0},
    {"Plus_Large", "999999+1", TestCalculatePlus, 999999.0, 1.0, 1000000.0},
    {"Plus_Small", "0.00001+0.00002", TestCalculatePlus, 1e-5, 2e-5, 3e-5},
    {"Plus_Float", "1234.567+8765.433", TestCalculatePlus, 1234.567, 8765.433,
     10000.0},
    {"Plus_Exp", "1e10+1e10", TestCalculatePlus, 1e10, 1e10, 2e10},

    {"Minus_Basic", "10-3", TestCalculateMinus, 10.0, 3.0, 7.0},
    {"Minus_Negative_Result", "3-10", TestCalculateMinus, 3.0, 10.0, -7.0},
    {"Minus_From_Neg", "-5-5", TestCalculateMinus, -5.0, 5.0, -10.0},
    {"Minus_Neg_Right", "5--5", TestCalculateMinus, 5.0, -5.0, 10.0},
    {"Minus_Both_Neg", "-5--5", TestCalculateMinus, -5.0, -5.0, 0.0},
    {"Minus_Zeros", "0-0", TestCalculateMinus, 0.0, 0.0, 0.0},
    {"Minus_To_Neg_Zero", "0--0", TestCalculateMinus, 0.0, -0.0, 0.0},
    {"Minus_Precision", "1000000-0.00001", TestCalculateMinus, 1000000.0, 1e-5,
     999999.99999},
    {"Minus_Exp", "1e5-5e4", TestCalculateMinus, 1e5, 5e4, 5e4},
    {"Minus_Identical", "-123.45--123.45", TestCalculateMinus, -123.45, -123.45,
     0.0},

    {"Multiply_Basic", "5*5", TestCalculateMultiply, 5.0, 5.0, 25.0},
    {"Multiply_Neg_Left", "-5*5", TestCalculateMultiply, -5.0, 5.0, -25.0},
    {"Multiply_Neg_Right", "5*-5", TestCalculateMultiply, 5.0, -5.0, -25.0},
    {"Multiply_Both_Neg", "-5*-5", TestCalculateMultiply, -5.0, -5.0, 25.0},
    {"Multiply_By_Zero_Right", "10*0", TestCalculateMultiply, 10.0, 0.0, 0.0},
    {"Multiply_By_Zero_Left", "0*-10", TestCalculateMultiply, 0.0, -10.0, 0.0},
    {"Multiply_Zeros", "0*0", TestCalculateMultiply, 0.0, 0.0, 0.0},
    {"Multiply_Identity", "123.45*1", TestCalculateMultiply, 123.45, 1.0,
     123.45},
    {"Multiply_Small", "0.001*0.001", TestCalculateMultiply, 0.001, 0.001,
     1e-6},
    {"Multiply_Large", "100000*100000", TestCalculateMultiply, 100000.0,
     100000.0, 1e10},

    {"Division_Basic", "100/4", TestCalculateDivision, 100.0, 4.0, 25.0},
    {"Division_Less_Than_One", "5/10", TestCalculateDivision, 5.0, 10.0, 0.5},
    {"Division_Neg_Left", "-20/5", TestCalculateDivision, -20.0, 5.0, -4.0},
    {"Division_Neg_Right", "20/-5", TestCalculateDivision, 20.0, -5.0, -4.0},
    {"Division_Both_Neg", "-20/-5", TestCalculateDivision, -20.0, -5.0, 4.0},
    {"Division_Zero_Top", "0/5", TestCalculateDivision, 0.0, 5.0, 0.0},
    {"Division_Identity", "123.45/1", TestCalculateDivision, 123.45, 1.0,
     123.45},
    {"Division_Periodic", "1/3", TestCalculateDivision, 1.0, 3.0, 0.3333333333},
    {"Division_By_Small", "1000/0.001", TestCalculateDivision, 1000.0, 0.001,
     1e6},
    {"Division_Exp", "1e5/1e2", TestCalculateDivision, 1e5, 1e2, 1000.0},

    {"DivByZero_Pos", "1/0", TestCalculateDivisionByZero, 1.0, 0.0, 0.0},
    {"DivByZero_Neg", "-1/0", TestCalculateDivisionByZero, -1.0, 0.0, 0.0},
    {"DivByZero_NaN", "0/0", TestCalculateDivisionByZero, 0.0, 0.0, 0.0},
    {"DivByZero_Large", "1e5/0", TestCalculateDivisionByZero, 1e5, 0.0, 0.0},
    {"DivByZero_Large_Neg", "-1e5/0", TestCalculateDivisionByZero, -1e5, 0.0,
     0.0},

    {"Pow_Basic", "2^3", TestCalculatePow, 2.0, 3.0, 8.0},
    {"Pow_Neg_Exp", "2^-3", TestCalculatePow, 2.0, -3.0, 0.125},
    {"Pow_Neg_Base_Odd", "-2^3", TestCalculatePow, -2.0, 3.0, -8.0},
    {"Pow_Neg_Base_Even", "-2^4", TestCalculatePow, -2.0, 4.0, 16.0},
    {"Pow_Zero_Exp", "5^0", TestCalculatePow, 5.0, 0.0, 1.0},
    {"Pow_Neg_Base_Zero_Exp", "-5^0", TestCalculatePow, -5.0, 0.0, 1.0},
    {"Pow_Zero_Base", "0^5", TestCalculatePow, 0.0, 5.0, 0.0},
    {"Pow_Identity_Exp", "10^1", TestCalculatePow, 10.0, 1.0, 10.0},
    {"Pow_One_Base", "1^100", TestCalculatePow, 1.0, 100.0, 1.0},
    {"Pow_Neg_One_Even_Exp", "-1^100", TestCalculatePow, -1.0, 100.0, 1.0},
    {"Pow_Neg_One_Odd_Exp", "-1^101", TestCalculatePow, -1.0, 101.0, -1.0},
    {"Pow_Float_Base", "0.5^2", TestCalculatePow, 0.5, 2.0, 0.25},
    {"Pow_Float_Exp", "4^0.5", TestCalculatePow, 4.0, 0.5, 2.0},
    {"Pow_Both_Float", "2.5^1.5", TestCalculatePow, 2.5, 1.5,
     3.952847075210474},
    {"Pow_Large_Exp", "10^5", TestCalculatePow, 10.0, 5.0, 100000.0},
    {"Pow_Exp_Base", "1e2^2", TestCalculatePow, 100.0, 2.0, 10000.0},

    {"NthRoot_Basic", "nthroot(8,3)", TestCalculateNthRoot, 8.0, 3.0, 2.0},
    {"NthRoot_Even", "nthroot(16,4)", TestCalculateNthRoot, 16.0, 4.0, 2.0},
    {"NthRoot_Odd", "nthroot(27,3)", TestCalculateNthRoot, 27.0, 3.0, 3.0},
    {"NthRoot_Identity", "nthroot(10,1)", TestCalculateNthRoot, 10.0, 1.0,
     10.0},
    {"NthRoot_One_Base", "nthroot(1,5)", TestCalculateNthRoot, 1.0, 5.0, 1.0},
    {"NthRoot_Zero_Base", "nthroot(0,3)", TestCalculateNthRoot, 0.0, 3.0, 0.0},
    {"NthRoot_Float_Base", "nthroot(0.25,2)", TestCalculateNthRoot, 0.25, 2.0,
     0.5},
    {"NthRoot_Float_Degree", "nthroot(8,1.5)", TestCalculateNthRoot, 8.0, 1.5,
     4.0},
    {"NthRoot_Large", "nthroot(1000000,6)", TestCalculateNthRoot, 1000000.0,
     6.0, 10.0},
    {"NthRoot_Neg_Base_Odd", "nthroot(-8,3)", TestCalculateNthRoot, -8.0, 3.0,
     -2.0},
    {"NthRoot_Neg_Base_Odd_Large", "nthroot(-27,3)", TestCalculateNthRoot,
     -27.0, 3.0, -3.0}};

TestSuite getCalculateSuite(void) {
  TestSuite suite;
  suite.tests = calculateTests;
  suite.count = sizeof(calculateTests) / sizeof(calculateTests[0]);
  return suite;
}

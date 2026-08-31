#include <math.h>
#include <stdbool.h>

#include "../src/calculate/calculate.h"
#include "testFunction.h"

static bool TestCalculateCos(const TestCase* self, double actualResult) {
  return ASSERT_CLOSE(actualResult, self->expected);
}

static bool TestCalculateSin(const TestCase* self, double actualResult) {
  return ASSERT_CLOSE(actualResult, self->expected);
}

static bool TestCalculateTan_Valid(const TestCase* self, double actualResult) {
  return ASSERT_CLOSE(actualResult, self->expected);
}

static bool TestCalculateCot_Valid(const TestCase* self, double actualResult) {
  return ASSERT_CLOSE(actualResult, self->expected);
}

static bool TestCalculateArcCos(const TestCase* self, double actualResult) {
  return ASSERT_CLOSE(actualResult, self->expected);
}

static bool TestCalculateArcSin(const TestCase* self, double actualResult) {
  return ASSERT_CLOSE(actualResult, self->expected);
}

static bool TestCalculateArcTan(const TestCase* self, double actualResult) {
  return ASSERT_CLOSE(actualResult, self->expected);
}

static bool TestCalculateArcCot(const TestCase* self, double actualResult) {
  return ASSERT_CLOSE(actualResult, self->expected);
}

static bool TestCalculateTan_Singularity(const TestCase* self,
                                         double actualResult) {
  (void)self;
  return isinf(actualResult) || isnan(actualResult);
}

static bool TestCalculateCot_Singularity(const TestCase* self,
                                         double actualResult) {
  (void)self;
  return isinf(actualResult) || isnan(actualResult);
}

static bool TestCalculateArcCos_InvalidInput(const TestCase* self,
                                             double actualResult) {
  (void)self;
  return isnan(actualResult);
}

static bool TestCalculateArcSin_InvalidInput(const TestCase* self,
                                             double actualResult) {
  (void)self;
  return isnan(actualResult);
}

static const TestCase trigonometricTests[] = {
    {"Cos_Zero", "cos(0)", TestCalculateCos, 0.0, 0.0, 1.0},
    {"Cos_60_Deg", "cos(1.04719755)", TestCalculateCos, 1.04719755, 0.0,
     0.50000000357},
    {"Cos_45_Deg", "cos(0.78539816)", TestCalculateCos, 0.78539816, 0.0,
     0.70710678118},
    {"Cos_90_Deg", "cos(1.57079632)", TestCalculateCos, 1.57079632, 0.0,
     0.00000000006},
    {"Cos_PI", "cos(3.14159265)", TestCalculateCos, 3.14159265, 0.0, -1.0},
    {"Cos_Neg_Angle", "cos(-1.04719755)", TestCalculateCos, -1.04719755, 0.0,
     0.50000000357},
    {"Cos_2PI", "cos(6.2831853)", TestCalculateCos, 6.2831853, 0.0, 1.0},
    {"Cos_Large_Reduction", "cos(100)", TestCalculateCos, 100.0, 0.0,
     0.86231887228},
    {"Cos_Large_Neg_Reduction", "cos(-50)", TestCalculateCos, -50.0, 0.0,
     0.96496602849},
    {"Cos_Small_Angle", "cos(0.00001)", TestCalculateCos, 1e-5, 0.0, 1.0},

    {"Sin_Zero", "sin(0)", TestCalculateSin, 0.0, 0.0, 0.0},
    {"Sin_30_Deg", "sin(0.52359877)", TestCalculateSin, 0.52359877, 0.0,
     0.49999999841},
    {"Sin_45_Deg", "sin(0.78539816)", TestCalculateSin, 0.78539816, 0.0,
     0.70710678118},
    {"Sin_90_Deg", "sin(1.57079632)", TestCalculateSin, 1.57079632, 0.0, 1.0},
    {"Sin_PI", "sin(3.14159265)", TestCalculateSin, 3.14159265, 0.0,
     0.00000000358},
    {"Sin_Neg_Angle", "sin(-0.52359877)", TestCalculateSin, -0.52359877, 0.0,
     -0.49999999841},
    {"Sin_270_Deg", "sin(4.71238898)", TestCalculateSin, 4.71238898, 0.0, -1.0},
    {"Sin_Large_Reduction", "sin(100)", TestCalculateSin, 100.0, 0.0,
     -0.50636564110},
    {"Sin_Large_Neg_Reduction", "sin(-50)", TestCalculateSin, -50.0, 0.0,
     0.26237485370},
    {"Sin_Small_Angle", "sin(0.00001)", TestCalculateSin, 1e-5, 0.0, 1e-5},

    {"Tan_Zero", "tan(0)", TestCalculateTan_Valid, 0.0, 0.0, 0.0},
    {"Tan_45_Deg", "tan(0.78539816)", TestCalculateTan_Valid, 0.78539816, 0.0,
     1.0},
    {"Tan_Neg_45", "tan(-0.78539816)", TestCalculateTan_Valid, -0.78539816, 0.0,
     -1.0},
    {"Tan_60_Deg", "tan(1.04719755)", TestCalculateTan_Valid, 1.04719755, 0.0,
     1.73205082103},
    {"Tan_PI", "tan(3.14159265)", TestCalculateTan_Valid, 3.14159265, 0.0, 0.0},
    {"Tan_Third_Quad", "tan(3.9269908)", TestCalculateTan_Valid, 3.9269908, 0.0,
     1.0},
    {"Tan_Large_Angle", "tan(10)", TestCalculateTan_Valid, 10.0, 0.0,
     0.64836082115},
    {"Tan_Large_Neg_Angle", "tan(-20)", TestCalculateTan_Valid, -20.0, 0.0,
     -2.23716094411},

    {"Cot_45_Deg", "cot(0.78539816)", TestCalculateCot_Valid, 0.78539816, 0.0,
     1.0},
    {"Cot_Neg_45", "cot(-0.78539816)", TestCalculateCot_Valid, -0.78539816, 0.0,
     -1.0},
    {"Cot_30_Deg", "cot(0.52359877)", TestCalculateCot_Valid, 0.52359877, 0.0,
     1.73205082103},
    {"Cot_90_Deg", "cot(1.57079632)", TestCalculateCot_Valid, 1.57079632, 0.0,
     0.0},
    {"Cot_Second_Quad", "cot(2.35619449)", TestCalculateCot_Valid, 2.35619449,
     0.0, -1.0},
    {"Cot_Large_Angle", "cot(10)", TestCalculateCot_Valid, 10.0, 0.0,
     1.54235104535},

    {"Tan_90_Singular", "tan(1.57079632)", TestCalculateTan_Singularity,
     1.57079632, 0.0, 0.0},
    {"Tan_270_Singular", "tan(4.71238898)", TestCalculateTan_Singularity,
     4.71238898, 0.0, 0.0},
    {"Cot_Zero_Singular", "cot(0)", TestCalculateCot_Singularity, 0.0, 0.0,
     0.0},
    {"Cot_PI_Singular", "cot(3.14159265)", TestCalculateCot_Singularity,
     3.14159265, 0.0, 0.0},

    {"ArcCos_One", "arccos(1)", TestCalculateArcCos, 1.0, 0.0, 0.0},
    {"ArcCos_Half", "arccos(0.5)", TestCalculateArcCos, 0.5, 0.0,
     1.04719755120},
    {"ArcCos_Zero", "arccos(0)", TestCalculateArcCos, 0.0, 0.0, 1.57079632679},
    {"ArcCos_Neg_Half", "arccos(-0.5)", TestCalculateArcCos, -0.5, 0.0,
     2.09439510239},
    {"ArcCos_Minus_One", "arccos(-1)", TestCalculateArcCos, -1.0, 0.0,
     3.14159265359},
    {"ArcCos_Sqrt2_Div2", "arccos(0.70710678)", TestCalculateArcCos, 0.70710678,
     0.0, 0.78539816339},

    {"ArcSin_Zero", "arcsin(0)", TestCalculateArcSin, 0.0, 0.0, 0.0},
    {"ArcSin_Half", "arcsin(0.5)", TestCalculateArcSin, 0.5, 0.0,
     0.52359877559},
    {"ArcSin_One", "arcsin(1)", TestCalculateArcSin, 1.0, 0.0, 1.57079632679},
    {"ArcSin_Neg_Half", "arcsin(-0.5)", TestCalculateArcSin, -0.5, 0.0,
     -0.52359877559},
    {"ArcSin_Minus_One", "arcsin(-1)", TestCalculateArcSin, -1.0, 0.0,
     -1.57079632679},
    {"ArcSin_Sqrt2_Div2", "arcsin(0.70710678)", TestCalculateArcSin, 0.70710678,
     0.0, 0.78539816339},

    {"ArcTan_Zero", "arctan(0)", TestCalculateArcTan, 0.0, 0.0, 0.0},
    {"ArcTan_One", "arctan(1)", TestCalculateArcTan, 1.0, 0.0, 0.78539816339},
    {"ArcTan_Neg_One", "arctan(-1)", TestCalculateArcTan, -1.0, 0.0,
     -0.78539816339},
    {"ArcTan_Sqrt3", "arctan(1.7320508)", TestCalculateArcTan, 1.7320508, 0.0,
     1.04719754408},
    {"ArcTan_Large_Inf", "arctan(1000)", TestCalculateArcTan, 1000.0, 0.0,
     1.56979632780},
    {"ArcTan_Large_Neg_Inf", "arctan(-1000)", TestCalculateArcTan, -1000.0, 0.0,
     -1.56979632780},

    {"ArcCot_Zero", "arccot(0)", TestCalculateArcCot, 0.0, 0.0, 1.57079632679},
    {"ArcCot_One", "arccot(1)", TestCalculateArcCot, 1.0, 0.0, 0.78539816339},
    {"ArcCot_Neg_One", "arccot(-1)", TestCalculateArcCot, -1.0, 0.0,
     2.35619449019},
    {"ArcCot_Sqrt3_Div3", "arccot(0.57735027)", TestCalculateArcCot, 0.57735027,
     0.0, 1.04719755319},
    {"ArcCot_Large", "arccot(1000)", TestCalculateArcCot, 1000.0, 0.0,
     0.00099999967},

    {"ArcCos_Too_Large", "arccos(2)", TestCalculateArcCos_InvalidInput, 2.0,
     0.0, 0.0},
    {"ArcCos_Too_Small", "arccos(-1.5)", TestCalculateArcCos_InvalidInput, -1.5,
     0.0, 0.0},
    {"ArcSin_Too_Large", "arcsin(5)", TestCalculateArcSin_InvalidInput, 5.0,
     0.0, 0.0},
    {"ArcSin_Too_Small", "arcsin(-10)", TestCalculateArcSin_InvalidInput, -10.0,
     0.0, 0.0}};

TestSuite getTrigonometricSuite(void) {
  TestSuite suite;
  suite.tests = trigonometricTests;
  suite.count = sizeof(trigonometricTests) / sizeof(trigonometricTests[0]);
  return suite;
}

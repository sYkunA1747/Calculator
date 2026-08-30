#ifndef TEST_FUNCTION_H
#define TEST_FUNCTION_H

#include <math.h>
#include <stdbool.h>
#include <string.h>
#include <strings.h>

#ifdef _WIN32
#define strcasecmp _stricmp
#endif


/*
*   testTrigonometricFunctions
*/

#ifndef M_PI_2
#define M_PI_2 1.57079632679489661923
#endif

#ifndef EPSILON
#define EPSILON 1e-10
#endif 

#define ASSERT_CLOSE(actual, expected) (fabs((actual)-(expected))< EPSILON)
#define ASSERT_TEST(actual, expected) (fabs((actual)-(expected))<EPSILON)

 
#define ASSERT_STR_EQ(expr, expected) (strcasecmp(FormatString(expr), (expected)) == 0)

/*
*  Function of calculate
*/

bool TestCalculatePlus(double numOne, double numTwo);
bool TestCalculateMinus(double numOne, double numTwo);
bool TestCalculateMultiply(double numOne, double numTwo);
bool TestCalculateDivision(double numOne, double numTwo);
bool TestCalculateNthRoot(double numOne, double numTwo);
bool TestCalculatePow(double numOne, double numTwo);

// Fucntion for testing trigonometric
bool TestCalculateCos(double angle);
bool TestCalculateSin(double angle);
bool TestCalculateTan(double angle);
bool TestCalculateCot(double angle);
bool TestCalculateArcCos(double angle);
bool TestCalculateArcSin(double angle);
bool TestCalculateArcTan(double angle);
bool TestCalculateArcCot(double angle);

/*============================================*/
/*            ВАЛИДНЫЕ                        */
/*              ЗНАЧЕНИЯ                      */
/*============================================*/

bool TestCalculateTan_Valid(double angle);
bool TestCalculateCot_Valid(double angle);

/*============================================*/
/*   ГРАНИЧНЫЕ УСЛОВИЯ / СИНГУЛЯРНОСТИ        */
/*   (БЕЗ макроса, с проверкой isinf/isnan)   */
/*============================================*/

bool TestCalculateTan_Singularity(void);
bool TestCalculateCot_Singularity(void);
bool TestCalculateArcCos_InvalidInput(void);
bool TestCalculateArcSin_InvalidInput(void);

/*
*  Function of parsing to string
*/

bool TestParseOneStr(void);
bool TestParseTwoStr(void);
bool TestParseThreeStr(void);



static inline char* FormatString(const char* expr) {
    return (char*)expr; 
}


/*************************************** */

#endif




#include "testFunction.h"
#include "../src/calculate/calculate.h" 

#include <stdbool.h>
#include <math.h>


bool TestCalculateCos(double angle){
    return ASSERT_CLOSE(CalculateCos(angle), cos(angle));
}


bool TestCalculateSin(double angle){
    return ASSERT_CLOSE(CalculateSin(angle), sin(angle));
}


bool TestCalculateTan_Valid(double angle){
    return ASSERT_CLOSE(CalculateTan(angle), tan(angle));
}


bool TestCalculateCot_Valid(double angle){
    return ASSERT_CLOSE(CalculateCot(angle), 1.00/tan(angle));
}


bool TestCalculateArcCos(double angle){
    return ASSERT_CLOSE(CalculateArcCos(angle), acos(angle));
}


bool TestCalculateArcSin(double angle){
    return ASSERT_CLOSE(CalculateArcSin(angle), asin(angle));
}


bool TestCalculateArcTan(double angle){    
    return ASSERT_CLOSE(CalculateArcTan(angle), atan(angle));
}


bool TestCalculateArcCot(double angle){    
    return ASSERT_CLOSE(CalculateArcCot(angle), (M_PI_2-atan(angle)));
}



/* ========================================== */
/* ГРАНИЧНЫЕ УСЛОВИЯ / СИНГУЛЯРНОСТИ          */
/* (БЕЗ макроса, с явной проверкой isinf/isnan) */
/* ========================================== */

bool TestCalculateTan_Singularity(void){
    double result = CalculateTan(M_PI_2);
    return isinf(result) || isnan(result);
}


bool TestCalculateCot_Singularity(void){
    double result = CalculateCot(0.0);
    return isinf(result) || isnan(result);   
}


bool TestCalculateArcCos_InvalidInput(void){
    double result = CalculateArcCos(2.0);
    return isnan(result);
}


bool TestCalculateArcSin_InvalidInput(void){
    double result = CalculateArcSin(-5.0);
    return isnan(result);
}

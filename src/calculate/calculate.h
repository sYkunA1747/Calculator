#ifndef CALCULATE_H
#define CALCULATE_H

#ifndef M_PI
#define M_PI  3.14159265358979323846
#endif

#ifndef M_PI_2
#define M_PI_2 1.57079632679489661923
#endif

#define M_SQRT3_INV 0.57735026918962576451
#define M_PI_6 0.52359877559829887307

double CalculatePlus(double numOne, double numTwo);
double CalculateMinus(double numOne, double numTwo);
double CalculateMultiply(double numOne, double numTwo);
double CalculateDivision(double numOne, double numTwo);
double CalculateNthRoot(double numOne, double numTwo);
double CalculatePow(double numOne, double numTwo);


// Fucntion for testing trigonometric
double CalculateCos(double angle);
double CalculateSin(double angle);
double CalculateTan(double angle);
double CalculateCot(double angle);
double CalculateArcCos(double angle);
double CalculateArcSin(double angle);
double CalculateBaseArcTan(double angle);
double CalculateArcTan(double angle);
double CalculateArcCot(double angle);



/*============================================*/
/*             Additional                     */
/*                Function                    */
/*============================================*/



#endif
#include "calculate.h"

#include <math.h>

static double normalize_angle(double angle){
    while(angle > M_PI) angle-=2.0*M_PI;
    while(angle < -M_PI) angle+=2.0*M_PI;
    return angle;
}


double CalculateCos(double angle){
    angle = normalize_angle(angle);

    double term = 1.0;
    double sum = 1.0;
    double angle_sq = angle*angle;

    for(int i = 2; fabs(term)>1e-15;i+=2){
        term= -term*angle_sq/(i*(i-1));
        sum+=term;
    }
    return sum;
}


double CalculateSin(double angle){
    double term = angle;
    double sum = angle;
    int number = 1;

    angle = normalize_angle(angle);

    do{
        term = -term*angle*angle/((2*number)*(2*number+1));
        sum+= term;
        number++;
    }while(fabs(term) > 1e-15);

    return sum;
}


double CalculateTan(double angle){
    double cosVal = CalculateCos(angle);
    if(fabs(cosVal)<1e-10)
        return INFINITY;
    return CalculateSin(angle)/cosVal;
}


double CalculateCot(double angle){
    double sinVal = CalculateSin(angle);
    if(fabs(sinVal)<1e-10)
        return INFINITY;
    return CalculateCos(angle)/sinVal;
}


double CalculateArcSin(double angle){
    if(angle<-1.0 || angle>1.0) return NAN;

    if(angle==1.0) return M_PI_2;
    if(angle==-1.0) return -M_PI_2;

    return CalculateArcTan(angle/sqrt(1.0-angle*angle));
}


double CalculateArcCos(double angle){
    if(angle<-1.0 || angle>1.0) return NAN;

    return M_PI_2 - CalculateArcSin(angle);
}


double CalculateBaseArcTan(double angle){
    double term = angle;
    double sum = angle;
    int i = 3;
    
    do{
        term=-term*angle*angle*(double)(i-2)/i;
        sum+=term;
        i+=2;
    }while(fabs(term)>1e-15);
    return sum;
}


double CalculateArcTan(double angle){
    if(angle>1.0) return M_PI_2-CalculateBaseArcTan(1.0/angle);
    else if(angle<-1.0) return -M_PI_2-CalculateBaseArcTan(1.0/angle);
    return CalculateBaseArcTan(angle);
}




double CalculateArcCot(double angle){
    return M_PI_2-CalculateArcTan(angle);
}




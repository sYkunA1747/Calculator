#include <math.h>

#include "calculate.h"

static double CalculateBaseArcTan(double angle);
static double normalize_angle(double angle);

static double normalize_angle(double angle) {
  if (!isfinite(angle)) return NAN;
  angle = fmod(angle, 2.0 * M_PI);
  while (angle > M_PI) angle -= 2.0 * M_PI;
  while (angle < -M_PI) angle += 2.0 * M_PI;
  return angle;
}

double CalculateCos(double angle) {
  angle = normalize_angle(angle);
  int sign = 1;
  if (angle > M_PI_2) {
    angle = M_PI - angle;
    sign = -1;
  } else if (angle < -M_PI_2) {
    angle = -M_PI - angle;
    sign = -1;
  }
  if (angle > M_PI / 4.0) return sign * CalculateSin(M_PI_2 - angle);
  if (angle < -M_PI / 4.0) return sign * CalculateSin(M_PI_2 + angle);
  double term = 1.0;
  double sum = 1.0;
  double angle_sq = angle * angle;

  for (int i = 2; fabs(term) > 1e-15 && i < 100; i += 2) {
    term = -term * angle_sq / (i * (i - 1));
    sum += term;
  }
  return sign * sum;
}

double CalculateSin(double angle) {
  angle = normalize_angle(angle);
  int sign = 1;
  if (angle > M_PI_2)
    angle = M_PI - angle;
  else if (angle < -M_PI_2)
    angle = -M_PI - angle;
  if (angle > M_PI / 4.0) return CalculateCos(M_PI_2 - angle);
  if (angle < -M_PI / 4.0) return -CalculateCos(M_PI_2 + angle);
  double term = angle;
  double sum = angle;
  int number = 1;
  do {
    term = -term * angle * angle / ((2 * number) * (2 * number + 1));
    sum += term;
    number++;
  } while (fabs(term) > 1e-15 && number < 100);
  return sign * sum;
}

double CalculateTan(double angle) {
  double sinVal = CalculateSin(angle);
  double cosVal = CalculateCos(angle);
  if (fabs(cosVal) < 1e-10) return copysign(INFINITY, sinVal * cosVal);
  ;
  return CalculateSin(angle) / cosVal;
}

double CalculateCot(double angle) {
  double sinVal = CalculateSin(angle);
  if (fabs(sinVal) < 1e-10)
    return copysign(INFINITY, sinVal * CalculateCos(angle));
  return CalculateCos(angle) / sinVal;
}

double CalculateArcSin(double angle) {
  if (angle < -1.0 || angle > 1.0) return NAN;

  if (angle == 1.0) return M_PI_2;
  if (angle == -1.0) return -M_PI_2;

  return CalculateArcTan(angle / sqrt(1.0 - angle * angle));
}

double CalculateArcCos(double angle) {
  if (angle < -1.0 || angle > 1.0) return NAN;

  return M_PI_2 - CalculateArcSin(angle);
}

static double CalculateBaseArcTan(double angle) {
  double term = angle;
  double sum = angle;
  int i = 3;

  do {
    term = -term * angle * angle * (double)(i - 2) / i;
    sum += term;
    i += 2;
  } while (fabs(term) > 1e-15);
  return sum;
}

double CalculateArcTan(double angle) {
  if (angle < 0.0) return -CalculateArcTan(-angle);
  if (angle > 1.0) return M_PI_2 - CalculateArcTan(1.0 / angle);
  if (angle > 0.4) {
    double nextAngle = (angle - M_SQRT3_INV) / (1.0 + angle * M_SQRT3_INV);
    return M_PI_6 + CalculateBaseArcTan(nextAngle);
  }
  return CalculateBaseArcTan(angle);
}

double CalculateArcCot(double angle) { return M_PI_2 - CalculateArcTan(angle); }

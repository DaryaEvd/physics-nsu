#include "coefficients.hpp"

#include <cmath>

double countSymmetricB(double k1, double k2, const int a) {
  return sqrt((k1 / ((cos(k2 * a / 2) * cos(k2 * a / 2)) +
                     k1 * (sin(k2 * a) / (2 * k2) + a / 2))));
}

double countAssymmetricB(double k1, double k2, const int a) {
  return sqrt((k1 / ((sin(k2 * a / 2) * sin(k2 * a / 2)) +
                     k1 * (-sin(k2 * a) / (2 * k2) + a / 2))));
}

double countSymmetricC(double k1, double k2, const int a, double B) {
  return B * cos(k2 * a / 2) * exp(k1 * a / 2);
}

double countAssymmetricC(double k1, double k2, const int a,
                         double B) {
  return B * sin(k2 * a / 2) * exp(k1 * a / 2);
}

double symmetricFunctionEquations(double x, double C, double B,
                                  double k1, double k2,
                                  double solution, double a) {
  if (x < 0) {
    return C * exp(k1 * x) + solution;
  } else if (x <= a) {
    return B * cos(k2 * x) + solution;
  } else {
    return C * exp(-k1 * x) + solution;
  }
}

double assymmetricFunctionEquations(double x, double C, double B,
                                    double k1, double k2,
                                    double solution, double a) {
  if (x < 0) {
    return -C * exp(k1 * x) + solution;
  } else if (x <= a) {
    return B * sin(k2 * x) + solution;
  } else {
    return C * exp(-k1 * x) + solution;
  }
}

#pragma once

double countSymmetricB(double k1, double k2, const int a);
double countAssymmetricB(double k1, double k2, const int a);
double countSymmetricC(double k1, double k2, const int a, double B);
double countAssymmetricC(double k1, double k2, const int a, double B);

double symmetricFunctionEquations(double x, double C, double B,
                                  double k1, double k2,
                                  double solution, double a);

double assymmetricFunctionEquations(double x, double C, double B,
                                    double k1, double k2,
                                    double solution, double a);

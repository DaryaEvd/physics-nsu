#pragma once

#include <vector>
std::vector<double> generatePoints(double start, double end,
                                   int amountOfNumbers);

std::vector<double> countEquation(const int amountOfNumbers,
                                  const double epsilon,
                                  std::vector<double> points,
                                  std::vector<double> left,
                                  std::vector<double> right);

double symmetricFunctionEquations(double x, double C, double B,
                                  double k1, double k2,
                                  double solution, double a);

double assymmetricFunctionEquations(double x, double C, double B,
                                    double k1, double k2,
                                    double solution, double a);

void countParts(const int amountOfNumbers,
                std::vector<double> &rightPart,
                std::vector<double> &tg, std::vector<double> &ctg,
                std::vector<double> &E, const int h, const int m,
                const int U_0, const int a);

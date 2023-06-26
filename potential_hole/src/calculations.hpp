#pragma once

#include <vector>
std::vector<double> generatePoints(double start, double end,
                                   int amountOfNumbers);

double countArgInCommonTan(double x, double a, double m, double U_0,
                           double h);
double countTanFunc(double x, double a, double m, double U_0,
                    double h);
double countCotanFunc(double x, double a, double m, double U_0,
                      double h);
double countRightFunc(double x, double U_0);
double countDiffRightTan(double x, double a, double m, double U_0,
                         double h);
double countDiffRightCotan(double x, double a, double m, double U_0,
                           double h);

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

std::vector<double> countIntersections(
    double leftSide, double rightSise, double a, double m, double U_0,
    double h,
    double (*countDiffFunc)(double, double, double, double, double));

double generateFunction(int level, double a, double m, double U_0,
                        double h);
                        
void countParts(const int amountOfNumbers,
                std::vector<double> &rightPart,
                std::vector<double> &tg, std::vector<double> &ctg,
                std::vector<double> &E, const int h, const int m,
                const int U_0, const int a);
#pragma once

#include <vector>

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

std::vector<double> solveEquation(
    double leftSide, double rightSise, double a, double m, double U_0,
    double h,
    double (*countDiffFunc)(double, double, double, double, double));

void countParts(const int amountOfNumbers,
                std::vector<double> &rightPart,
                std::vector<double> &tg, std::vector<double> &ctg,
                std::vector<double> &E, const int h, const int m,
                const int U_0, const int a);

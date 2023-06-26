#include "calculations.hpp"

#include <cmath>
#include <iostream>

double countArgInCommonTan(double e, double a, double m, double U_0,
                           double h) {
  return a * std::sqrt(2 * m * (e + U_0)) / (2 * h);
}

double countTanFunc(double e, double a, double m, double U_0,
                    double h) {
  return std::sin(countArgInCommonTan(e, a, m, U_0, h)) /
         std::cos(countArgInCommonTan(e, a, m, U_0, h));
}

double countCotanFunc(double e, double a, double m, double U_0,
                      double h) {
  return 1 / countTanFunc(e, a, m, U_0, h);
}

double countRightFunc(double e, double U_0) {
  return std::sqrt(std::abs(e) / (U_0 + e));
}

double countDiffRightTan(double e, double a, double m, double U_0,
                         double h) {
  return countRightFunc(e, U_0) - countTanFunc(e, a, m, U_0, h);
}

double countDiffRightCotan(double e, double a, double m, double U_0,
                           double h) {
  return countRightFunc(e, U_0) - countCotanFunc(e, a, m, U_0, h);
}

void countParts(const int amountOfNumbers,
                std::vector<double> &rightPart,
                std::vector<double> &tg, std::vector<double> &ctg,
                std::vector<double> &E, const int h, const int m,
                const int U_0, const int a) {
  for (int i = 0; i < amountOfNumbers; i++) {
    rightPart[i] = countRightFunc(E[i], U_0);
    tg[i] = countTanFunc(E[i], a, m, U_0, h);
    ctg[i] = countCotanFunc(E[i], a, m, U_0, h);
  }
}

std::vector<double> solveEquation(
    double leftSide, double rightSise, double a, double m, double U_0,
    double h,
    double (*countDiffFunc)(double, double, double, double, double)) {

  std::vector<double> resultIntersections;
  double epsilon = 0.00000001;

  while (rightSise - leftSide > epsilon) {
    double mid = (leftSide + rightSise) / 2;
    if (countDiffFunc(mid, a, m, U_0, h) > 0) {
      leftSide = mid;
    } else {
      rightSise = mid;
    }
  }

  resultIntersections.push_back(leftSide);
  return resultIntersections;
}

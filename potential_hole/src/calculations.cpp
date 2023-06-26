#include "calculations.hpp"

#include <cmath>
#include <iostream>

std::vector<double> generatePoints(double start, double end,
                                   int amountOfNumbers) {
  std::vector<double> pointsArray(amountOfNumbers);
  double step = (end - start) / amountOfNumbers;
  for (int i = 0; i < amountOfNumbers; i++) {
    pointsArray[i] = start + i * step;
  }

  return pointsArray;
}

double countArgInCommonTan(double x, double a, double m, double U_0,
                           double h) {
  return a * std::sqrt(2 * m * (x + U_0)) / (2 * h);
}

double countTanFunc(double x, double a, double m, double U_0,
                    double h) {
  return std::sin(countArgInCommonTan(x, a, m, U_0, h)) /
         std::cos(countArgInCommonTan(x, a, m, U_0, h));
}

double countCotanFunc(double x, double a, double m, double U_0,
                      double h) {
  return 1 / countTanFunc(x, a, m, U_0, h);
}

double countRightFunc(double x, double U_0) {
  return std::sqrt(std::abs(x) / (U_0 + x));
}

double countDiffRightTan(double x, double a, double m, double U_0,
                         double h) {
  return countRightFunc(x, U_0) - countTanFunc(x, a, m, U_0, h);
}

double countDiffRightCotan(double x, double a, double m, double U_0,
                           double h) {
  return countRightFunc(x, U_0) - countCotanFunc(x, a, m, U_0, h);
}

std::vector<double> countEquation(const int amountOfNumbers,
                                  const double epsilon,
                                  std::vector<double> points,
                                  std::vector<double> left,
                                  std::vector<double> right) {
  std::vector<double> intersections;
  int U_0 = 1;
  int m = 1;
  int h = 1;
  int a = 1;

  for (int i = 0; i < amountOfNumbers - 1; i++) {
    double r = right.at(i);
    double l = left.at(i);

    while (std::abs(l - r) > epsilon) {
      double mid = (l + r) / 2;
      if ((1 / std::sqrt((U_0 / std::abs(mid - 1)))) *
              std::tan((std::sqrt(2 * m * (l + U_0)) * a / (2 * h))) <
          0) {
        r = mid;
      } else if ((1 / std::sqrt((U_0 / std::abs(mid - 1)))) *
                     std::tan((std::sqrt(2 * m * (r + U_0)) * a /
                               (2 * h))) <
                 0) {
        l = mid;
      } else {
        mid = 0;
        break;
      }
    }
  }

  return intersections;
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

std::vector<double> countIntersections(
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

double generateFunction(int level, double a, double m, double U_0,
                        double h) {
  double numerator = M_PI * h * (1 + 2 * level);
  double numeratorInSquare = numerator * numerator;
  double denominator = (2 * m * a * a);
  return numeratorInSquare / denominator - U_0;
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

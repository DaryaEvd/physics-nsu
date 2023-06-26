#include "generateValues.hpp"

#include <cmath>

std::vector<double> generatePoints(double start, double end,
                                   int amountOfNumbers) {
  std::vector<double> pointsArray(amountOfNumbers);
  double step = (end - start) / amountOfNumbers;
  for (int i = 0; i < amountOfNumbers; i++) {
    pointsArray[i] = start + i * step;
  }

  return pointsArray;
}

double generateFunction(int level, double a, double m, double U_0,
                        double h) {
  double numerator = M_PI * h * (1 + 2 * level);
  double numeratorInSquare = numerator * numerator;
  double denominator = (2 * m * a * a);
  return numeratorInSquare / denominator - U_0;
}

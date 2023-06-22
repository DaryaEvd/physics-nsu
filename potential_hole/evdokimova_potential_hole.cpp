#include "matplotlibcpp.h"

#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <vector>

using namespace std;

namespace plt = matplotlibcpp;

std::vector<double> generatePoints(double start, double end,
                                   int amountOfNumbers) {
  std::vector<double> pointsArray(amountOfNumbers);
  double step = (end - start) / amountOfNumbers;
  for (int i = 0; i < amountOfNumbers; i++) {
    pointsArray[i] = start + i * step;
  }

  return pointsArray;
}

std::vector<double> findSolutions(const int amountOfNumbers,
                                  const double epsilon,
                                  std::vector<double> points,
                                  std::vector<double> left,
                                  std::vector<double> right) {
  std::vector<double> intersections;
  for (int i = 0; i < amountOfNumbers; i++) {
    if (std::abs(right[i] - left[i]) < epsilon) {
      intersections.push_back(points[i]);
    }
  }
  return intersections;
}

int main(int argc, char **argv) {
  // argv[1] = a - width of hole
  if (argc != 2) {
    std::cout << "Width of hole is needed" << std::endl;
    return 0;
  }

  if (argv[1] < 0) {
    std::cout << "Error! Width should be > 0" << std::endl;
  }

  const int a = std::atoi(argv[1]); // ширина ямы

  const int m = 1;
  const int h = 1;
  const int U_0 = 1;

  const int amountOfNumbers = 100000;
  std::vector<double> E = generatePoints(0, -1, amountOfNumbers);

  vector<double> tg(amountOfNumbers);
  vector<double> ctg(amountOfNumbers);
  vector<double> rightPart(amountOfNumbers);

  vector<double> xAxis(amountOfNumbers, 0);

  for (int i = 0; i < amountOfNumbers; i++) {
    rightPart[i] = 1 / std::sqrt((U_0 / std::abs(E[i]) - 1));
    tg[i] = std::tan((std::sqrt(2 * m * (E[i] + U_0)) * a / (2 * h)));
    double tan = tg[i];
    ctg[i] = -1 / tan;
  }

  const double epsilon = 0.0001;

  std::vector<double> intersectionsRightTg =
      findSolutions(amountOfNumbers, epsilon, E, tg, rightPart);

  std::cout << "Intersection for symmetric function: " << std::endl;
  for (int i = 0; i < intersectionsRightTg.size(); i++) {
    std::cout << "#" << i + 1 << ": " << std::fixed
              << std::setprecision(7) << intersectionsRightTg[i]
              << std::endl;
  }

  std::vector<double> intersectionsRightCtg =
      findSolutions(amountOfNumbers, epsilon, E, ctg, rightPart);

  std::cout << "========================================"
            << std::endl;
  std::cout << "Intersection for assymmetric function: " << std::endl;
  for (int i = 0; i < intersectionsRightCtg.size(); i++) {
    std::cout << "#" << i + 1 << ": " << std::fixed
              << std::setprecision(7) << intersectionsRightCtg[i]
              << std::endl;
  }

  std::cout << "===== intersections found ======" << std::endl;

  plt::plot(E, rightPart);
  plt::plot(E, tg);
  plt::plot(E, ctg);

  plt::plot(E, xAxis);
  plt::show();

  return 0;
}

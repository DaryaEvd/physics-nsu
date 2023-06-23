#include "matplotlibcpp.h"

#include "calculations.hpp"
#include "consoleOutput.hpp"
#include "drawingFigures.hpp"

#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <limits>
#include <vector>

namespace plt = matplotlibcpp;

int main(int argc, char **argv) {
  // argv[1] = a - width of hole
  if (argc != 2) {
    std::cout << "Width of hole is needed as argument to main"
              << std::endl;
    return 0;
  }

  if (std::atoi(argv[1]) < 0) {
    std::cout << "Error! Width should be > 0" << std::endl;
  }

  const int a = std::atoi(argv[1]); // ширина ямы

  const int m = 1;
  const int h = 1;
  const int U_0 = 1;

  const int amountOfNumbers = 250000;
  std::vector<double> E = generatePoints(0, -1, amountOfNumbers);

  std::vector<double> tg(amountOfNumbers);
  std::vector<double> ctg(amountOfNumbers);
  std::vector<double> rightPart(amountOfNumbers);

  std::vector<double> xAxis(amountOfNumbers, 0);

  for (int i = 0; i < amountOfNumbers; i++) {
    rightPart[i] = 1 / std::sqrt((U_0 / std::abs(E[i]) - 1));
    tg[i] = std::tan((std::sqrt(2 * m * (E[i] + U_0)) * a / (2 * h)));
    double tan = tg[i];
    ctg[i] = 1 / tan;
  }

  const double epsilon = 0.0001;

  std::vector<double> intersectionsRightTg =
      countEquation(amountOfNumbers, epsilon, E, tg, rightPart);

  std::cout << "Intersections for symmetric function: " << std::endl;
  printOutput(intersectionsRightTg);

  std::vector<double> intersectionsRightCtg =
      countEquation(amountOfNumbers, epsilon, E, ctg, rightPart);

  std::cout << "Intersections for assymmetric function: "
            << std::endl;
  printOutput(intersectionsRightCtg);

  std::cout << "===== intersections found ======" << std::endl;

  drawWithNormScale(rightPart);
  drawWithNormScale(tg);
  drawWithNormScale(ctg);

  plt::plot(E, rightPart);
  plt::plot(E, tg);
  plt::plot(E, ctg);

  plt::plot(E, xAxis);
  plt::show();

  plt::close();

  return 0;
}

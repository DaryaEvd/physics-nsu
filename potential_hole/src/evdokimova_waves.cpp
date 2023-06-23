#include "matplotlibcpp.h"

#include "calculations.hpp"
#include "coefficient.hpp"
#include "consoleOutput.hpp"
#include "drawingFigures.hpp"
#include "drawingWaves.hpp"

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

  countParts(amountOfNumbers, rightPart, tg, ctg, E, h, m, U_0, a);

  const double epsilon = 0.0001;

  std::vector<double> intersectionsRightTg =
      countEquation(amountOfNumbers, epsilon, E, tg, rightPart);

  std::vector<double> intersectionsRightCtg =
      countEquation(amountOfNumbers, epsilon, E, ctg, rightPart);

  createHole(U_0, a, amountOfNumbers);

  // uncomment this to see Symmetric function's levels
  // /*
  // std::vector<double> levelsTan =
  //     generatePoints(0, a, amountOfNumbers);
  // for (double solution : intersectionsRightTg) {
  //   std::vector<double> numbers(levelsTan.size(), solution);
  //   plt::plot(levelsTan, numbers);
  // }

  // drawSymmetricWaveFunction(intersectionsRightTg, h, m, U_0, a);

  // uncomment this to see Assymmetric function's levels
  // /*
  std::vector<double> levelsCotan =
      generatePoints(0, a, amountOfNumbers);
  for (double solution : intersectionsRightCtg) {
    std::vector<double> numbers(levelsCotan.size(), solution);
    plt::plot(levelsCotan, numbers);
    plt::title("Assymetric wave functions");
  }

  drawAssymmetricWaveFunction(intersectionsRightCtg, h, m, U_0, a);

  // */

  plt::show();
  plt::close();

  return 0;
}

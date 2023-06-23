#include "matplotlibcpp.h"

#include "calculations.hpp"
#include "coefficients.hpp"
#include "consoleOutput.hpp"
#include "drawingFigures.hpp"
#include "drawingLevels.hpp"
#include "drawingWaves.hpp"

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

  plt::plot({0}); //DON'T DELETE THIS LINE! OTHERWISE YOU GOT SEG FAULT

  createHole(U_0, a, amountOfNumbers);

  // uncomment a section below to see Symmetric function's levels and
  // waves
  // /*
  std::vector<double> levelsTan =
      generatePoints(0, a, amountOfNumbers);
  drawLevels(levelsTan, intersectionsRightTg);
  drawSymmetricWaveFunction(intersectionsRightTg, h, m, U_0, a);
  plt::title("Symmetric wave functions");
  // */

  // uncomment a section below to see Assymmetric function's levels
  // /*
  // std::vector<double> levelsCotan =
  //     generatePoints(0, a, amountOfNumbers);
  // drawLevels(levelsCotan, intersectionsRightCtg);

  // for (double solution : intersectionsRightCtg) {
  //   std::vector<double> numbers(levelsCotan.size(), solution);
  //   plt::plot(levelsCotan, numbers, "gray");
  // }

  // drawAssymmetricWaveFunction(intersectionsRightCtg, h, m, U_0, a);
  // plt::title("Assymmetric wave functions");
  // */

  plt::show();
  plt::close();

  return 0;
}

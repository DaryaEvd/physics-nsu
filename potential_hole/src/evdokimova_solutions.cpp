#include "matplotlibcpp.h"

#include "calculations.hpp"
#include "checkInput.hpp"
#include "consoleOutput.hpp"
#include "drawingFigures.hpp"
#include "generateValues.hpp"

namespace plt = matplotlibcpp;

int main(int argc, char **argv) {
  // argv[1] = a - width of hole
  if (argc != 2) {
    std::cout << "Width of hole is needed as argument to main"
              << std::endl;
    return 0;
  }

  if (!isOkWidthInput(argv[1])) {
    std::cout << "Error! Width should be a number!" << std::endl;
    return 0;
  }

  if (std::atoi(argv[1]) < 0) {
    std::cout << "Error! Width should be > 0" << std::endl;
    return 0;
  }

  const int a = std::atoi(argv[1]); // width of the hole

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

  std::vector<double> intersectionsRightTg;
  int maxBoundSymm = 0;
  while (generateFunction(maxBoundSymm, a, m, U_0, h) < 0) {
    maxBoundSymm++;
  }
  for (int e = -1; e < maxBoundSymm - 1; e++) {
    double leftSide = generateFunction(e, a, m, U_0, h);
    double rightSise = generateFunction(e + 1, a, m, U_0, h);
    if (rightSise > 0) {
      rightSise = 0;
    }
    std::vector<double> temp =
        solveEquation(leftSide + epsilon, rightSise - epsilon, a,
                           m, U_0, h, countDiffRightTan);
    intersectionsRightTg.insert(intersectionsRightTg.end(),
                                temp.begin(), temp.end());
  }
  std::cout << "Intersections for symmetric function: " << std::endl;
  printOutput(intersectionsRightTg);

  int maxBoundAssym = 0;
  while (generateFunction(maxBoundAssym, a, m, U_0, h) < 0) {
    maxBoundAssym++;
  }
  std::vector<double> intersectionsRightCtg;
  for (int e = -1; e < maxBoundAssym - 1; e++) {
    double leftSide = generateFunction(e, a, m, U_0, h);
    double rightSise = generateFunction(e + 1, a, m, U_0, h);
    if (rightSise > 0) {
      rightSise = 0;
    }
    std::vector<double> temp =
        solveEquation(leftSide + epsilon, rightSise - epsilon, a,
                           m, U_0, h, countDiffRightCotan);
    intersectionsRightCtg.insert(intersectionsRightCtg.end(),
                                 temp.begin(), temp.end());
  }
  std::cout << "Intersections for assymmetric function: " << std::endl;
  printOutput(intersectionsRightCtg);

  std::cout << "===== intersections found ======" << std::endl;

  drawWithNormScale(rightPart);
  drawWithNormScale(tg);
  drawWithNormScale(ctg);

  plt::plot(E, rightPart);
  plt::plot(E, tg);
  plt::plot(E, ctg);

  plt::plot(E, xAxis);

  plt::title("Solutions");

  plt::show();
  plt::close();

  return 0;
}

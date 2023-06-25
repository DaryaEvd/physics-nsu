#include "matplotlibcpp.h"

#include "calculations.hpp"
#include "checkInput.hpp"
#include "coefficients.hpp"
#include "consoleOutput.hpp"
#include "drawingFigures.hpp"
#include "drawingLevels.hpp"
#include "drawingWaves.hpp" // DELETE !!!

namespace plt = matplotlibcpp;
 
/*
TODO: decompose as bin search + put functions as args to funcs
*/

std::vector<double> countSymmIntersections(double leftSide,
                                           double rightSise, double a,
                                           double m, double U_0,
                                           double h) {
  std::vector<double> resultIntersections;
  double epsilon = 0.00000001;

  while (rightSise - leftSide > epsilon) {
    double mid = (leftSide + rightSise) / 2;
    if (countDiffRightTan(mid, a, m, U_0, h) > 0) {
      leftSide = mid;
    } else {
      rightSise = mid;
    }
  }

  resultIntersections.push_back(leftSide);
  return resultIntersections;
}

std::vector<double> countAssymmIntersections(double leftSide,
                                             double rightSise,
                                             double a, double m,
                                             double U_0, double h) {
  std::vector<double> resultIntersections;
  double epsilon = 0.00000001;

  while (rightSise - leftSide > epsilon) {
    double mid = (leftSide + rightSise) / 2;
    if (countDiffRightCotan(mid, a, m, U_0, h) > 0) {
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

int main(int argc, char **argv) {
  // argv[1] = a - width of hole
  // argv[2] - type of wave (symmetric or assymmetric)
  if (argc != 3) {
    std::cout << "Input: [width of hole] [type of wave: 's' or 'a']"
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

  if (!isOkTypeWave(argv[2])) {
    std::cout << "Error! Type of wave is 's' or 'a'" << std::endl;
    return 0;
  }

  const int a = std::atoi(argv[1]);            // ширина ямы
  const unsigned char typeOfWave = argv[2][0]; // тип волны

  const int m = 1;
  const int h = 1;
  const int U_0 = 1;

  const int amountOfNumbers = 250000;
  std::vector<double> E = generatePoints(0, -1, amountOfNumbers);

  std::vector<double> tg(amountOfNumbers);
  std::vector<double> ctg(amountOfNumbers);
  std::vector<double> rightPart(amountOfNumbers);

  std::vector<double> xAxis(amountOfNumbers, 0);

  const double epsilon = 0.00000001;

  std::vector<double> result;
  int maxE = 0;
  while (generateFunction(maxE, a, m, U_0, h) < 0) {
    maxE++;
  }

  plt::plot(
      {0}); // DON'T DELETE THIS LINE! OTHERWISE YOU GOT SEG FAULT

  createHole(U_0, a, amountOfNumbers);
  std::vector<double> levels = generatePoints(0, a, amountOfNumbers);
  drawLevels(levels, result);

  if (typeOfWave == 's') {
    //   std::vector<double> levelsTan =
    //       generatePoints(0, a, amountOfNumbers);
    //   drawLevels(levelsTan, intersectionsRightTg);

    for (int e = -1; e < maxE - 1; e++) {
      double leftSide = generateFunction(e, a, m, U_0, h);
      double rightSise = generateFunction(e + 1, a, m, U_0, h);
      if (rightSise > 0) {
        rightSise = 0;
      }
      std::vector<double> temp = countSymmIntersections(
          leftSide + epsilon, rightSise - epsilon, a, m, U_0, h);
      result.insert(result.end(), temp.begin(), temp.end());
    }

    printOutput(result);

    drawSymmetricWaveFunction(result, h, m, U_0, a);

    plt::title("Symmetric function's levels");
  }

  else if (typeOfWave == 'a') {
    // std::vector<double> levelsCotan =
    //     generatePoints(0, a, amountOfNumbers);
    // drawLevels(levelsCotan, intersectionsRightCtg);
    // plt::title("Assymetric function'l levels");

    for (int e = -1; e < maxE - 1; e++) {
      double leftSide = generateFunction(e, a, m, U_0, h);
      double rightSise = generateFunction(e + 1, a, m, U_0, h);
      if (rightSise > 0) {
        rightSise = 0;
      }
      std::vector<double> temp = countAssymmIntersections(
          leftSide + epsilon, rightSise - epsilon, a, m, U_0, h);
      result.insert(result.end(), temp.begin(), temp.end());
    }

    printOutput(result);

    plt::title("Assymmetric function's levels");
  }

  plt::show();
  plt::close();

  return 0;
}

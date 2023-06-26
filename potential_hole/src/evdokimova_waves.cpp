#include "matplotlibcpp.h"

#include "calculations.hpp"
#include "checkInput.hpp"
#include "coefficients.hpp"
#include "consoleOutput.hpp"
#include "drawingFigures.hpp"
#include "drawingLevels.hpp"
#include "drawingWaves.hpp"

namespace plt = matplotlibcpp;

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

  const double epsilon = 0.0001;

  plt::plot(
      {0}); // DON'T DELETE THIS LINE! OTHERWISE YOU GOT SEG FAULT

  createHole(U_0, a, amountOfNumbers);

  int maxBound = 0;
  while (generateFunction(maxBound, a, m, U_0, h) < 0) {
    maxBound++;
  }
  std::vector<double> result;

  if (typeOfWave == 's') {
    for (int e = -1; e < maxBound - 1; e++) {
      double leftSide = generateFunction(e, a, m, U_0, h);
      double rightSise = generateFunction(e + 1, a, m, U_0, h);
      if (rightSise > 0) {
        rightSise = 0;
      }
      std::vector<double> temp =
          countIntersections(leftSide + epsilon, rightSise - epsilon,
                             a, m, U_0, h, countDiffRightTan);
      result.insert(result.end(), temp.begin(), temp.end());
    }

    printOutput(result);

    drawSymmetricWaveFunction(result, h, m, U_0, a);
    plt::title("Symmetric wave functions");
  }

  else if (typeOfWave == 'a') {
    for (int e = -1; e < maxBound - 1; e++) {
      double leftSide = generateFunction(e, a, m, U_0, h);
      double rightSise = generateFunction(e + 1, a, m, U_0, h);
      if (rightSise > 0) {
        rightSise = 0;
      }
      std::vector<double> temp =
          countIntersections(leftSide + epsilon, rightSise - epsilon,
                             a, m, U_0, h, countDiffRightCotan);
      result.insert(result.end(), temp.begin(), temp.end());
    }

    drawAssymmetricWaveFunction(result, h, m, U_0, a);
    plt::title("Assymmetric wave functions");
  }

  std::vector<double> levels = generatePoints(0, a, amountOfNumbers);
  drawLevels(levels, result);

  plt::show();
  plt::close();

  return 0;
}

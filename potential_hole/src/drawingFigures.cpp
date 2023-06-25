#include "matplotlibcpp.h"

#include "drawingFigures.hpp"
#include "calculations.hpp"

#include <algorithm>
#include <cmath>
#include <limits>
#include <vector>

namespace plt = matplotlibcpp;

void drawWithNormScale(std::vector<double> &line) {
  const int maxScaleOnYAxis = 10;
  std::vector<double>::iterator it;
  for (it = line.begin(); it != line.end(); ++it) {
    if (abs(*it) > maxScaleOnYAxis) {
      line.erase(it);
      line.insert(it, std::numeric_limits<double>::quiet_NaN());
    }
  }
}

void createHole(const int U, const int a, const int amountOfNumbers) {
  std::vector<double> verticalWall =
      generatePoints(-U, 0, amountOfNumbers);
  std::vector<double> leftVertic(amountOfNumbers, 0);
  std::vector<double> rightVertic(amountOfNumbers, 2 * a);

  std::vector<double> cornerLeftX =
      generatePoints(0, -a, amountOfNumbers);
  std::vector<double> cornerLeftY(cornerLeftX.size(), 0);

  std::vector<double> bottomX = generatePoints(0, 2 * a, amountOfNumbers);
  std::vector<double> bottomY(bottomX.size(), -U);

  std::vector<double> cornerRightX =
      generatePoints(2 * a, 2 * a + a, amountOfNumbers);
  std::vector<double> cornerRightY(cornerRightX.size(), 0);

  plt::plot(cornerLeftX, cornerLeftY, "blue");
  plt::plot(leftVertic, verticalWall, "blue");
  plt::plot(bottomX, bottomY, "blue");
  plt::plot(rightVertic, verticalWall, "blue");
  plt::plot(cornerRightX, cornerRightY, "blue");
}
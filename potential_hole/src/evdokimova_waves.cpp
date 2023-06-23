#include "matplotlibcpp.h"

#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <limits>
#include <vector>

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

std::vector<double> countEquation(const int amountOfNumbers,
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

void printOutput(std::vector<double> intersections) {
  for (size_t i = 0; i < intersections.size(); i++) {
    std::cout << "#" << i + 1 << ": " << std::fixed
              << std::setprecision(7) << intersections[i]
              << std::endl;
  }
  std::cout << "========================================"
            << std::endl;
}

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
  std::vector<double> rightVertic(amountOfNumbers, a);

  std::vector<double> cornerLeftX =
      generatePoints(0, -a, amountOfNumbers);
  std::vector<double> cornerLeftY(cornerLeftX.size(), 0);

  std::vector<double> bottomX = generatePoints(0, a, amountOfNumbers);
  std::vector<double> bottomY(bottomX.size(), -U);

  std::vector<double> cornerRightX =
      generatePoints(a, 2 * a, amountOfNumbers);
  std::vector<double> cornerRightY(cornerRightX.size(), 0);

  plt::plot(cornerLeftX, cornerLeftY, "blue");
  plt::plot(leftVertic, verticalWall, "blue");
  plt::plot(bottomX, bottomY, "blue");
  plt::plot(rightVertic, verticalWall, "blue");
  plt::plot(cornerRightX, cornerRightY, "blue");
}

double symmetricFunctionEquations(double x, double C, double B, double k1,
                    double k2, double solution, double a) {
  if (x < 0) {
    return C * exp(k1 * x) + solution;
  } else if (x <= a) {
    return B * cos(k2 * x) + solution;
  } else {
    return C * exp(-k1 * x) + solution;
  }
}

double assymmetricFunctionEquations(double x, double C, double B, double k1,
                    double k2, double solution, double a) {
  if (x < 0) {
    return C * exp(k1 * x) + solution;
  } else if (x <= a) {
    return B * sin(k2 * x) + solution;
  } else {
    return C * exp(-k1 * x) + solution;
  }
}

void countParts(const int amountOfNumbers,
                std::vector<double> &rightPart,
                std::vector<double> &tg, std::vector<double> &ctg,
                std::vector<double> &E, const int h, const int m,
                const int U_0, const int a) {
  for (int i = 0; i < amountOfNumbers; i++) {
    rightPart[i] = 1 / std::sqrt((U_0 / std::abs(E[i]) - 1));
    tg[i] = std::tan((std::sqrt(2 * m * (E[i] + U_0)) * a / (2 * h)));
    double tan = tg[i];
    ctg[i] = 1 / tan;
  }
}

void drawSymmetricWaveFunction(std::vector<double> intersections,
                               const int h, const int m,
                               const int U_0, const int a) {
  for (double solution : intersections) {
    double k2 = sqrt(2 * m * (solution + U_0)) / h; // inside
    double k1 = sqrt(2 * m * abs(solution)) / h;    // outside

    double B =
        sqrt((k1 / ((cos(k2 * a / 2) * cos(k2 * a / 2)) +
                    k1 * (sin(k2 * a) + 1 / (2 * k2) + a / 2))));
    double C = B * cos(k2 * a / 2) * exp(k1 * a / 2);

    std::vector<double> x = generatePoints(0, a, 10000);
    std::vector<double> waveFuncArray(x.size());

    for (size_t i = 0; i < x.size(); i++) {
      waveFuncArray[i] =
          symmetricFunctionEquations(x[i], C, B, k1, k2, solution, a);
    }

    plt::plot(x, waveFuncArray);
  }
}

void drawAssymmetricWaveFunction(std::vector<double> intersections,
                                 const int h, const int m,
                                 const int U_0, const int a) {
  for (double solution : intersections) {
    double k2 = sqrt(2 * m * (solution + U_0)) / h; // inside
    double k1 = sqrt(2 * m * abs(solution)) / h;    // outside

    double B =
        sqrt((k1 / ((sin(k2 * a / 2) * sin(k2 * a / 2)) +
                    k1 * (-sin(k2 * a) + 1 / (2 * k2) + a / 2))));
    double C = B * sin(k2 * a / 2) * exp(k1 * a / 2);

    std::vector<double> x = generatePoints(0, a, 10000);
    std::vector<double> waveFuncArray(x.size());

    for (size_t i = 0; i < x.size(); i++) {
      waveFuncArray[i] =
          assymmetricFunctionEquations(x[i], C, B, k1, k2, solution, a);
    }

    plt::plot(x, waveFuncArray);
  }
}

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

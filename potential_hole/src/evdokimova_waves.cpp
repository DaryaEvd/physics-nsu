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
      findSolutions(amountOfNumbers, epsilon, E, tg, rightPart);

  std::vector<double> intersectionsRightCtg =
      findSolutions(amountOfNumbers, epsilon, E, ctg, rightPart);

  createHole(U_0, a, amountOfNumbers);

  // uncomment this to see Symmetric function's levels
  // /*
  // std::vector<double> levelsTan =
  //     generatePoints(0, a, amountOfNumbers);
  // for (double solution : intersectionsRightTg) {
  //   std::vector<double> numbers(levelsTan.size(), solution);
  //   plt::plot(levelsTan, numbers);
  // }

  for (double solution : intersectionsRightTg) {
    double k2 = sqrt(2 * m * (solution + U_0)) / h; // inside hole
    double k1 = sqrt(2 * m * abs(solution)) / h;    // outside hole

    // count coefficients:
    // double B =
    //     sqrt(exp(k1 * a) * exp(k1 * a) + (k1 / k2) * (k1 / k2)) /
    //     cos(k2 * a);

    // double C =
    //     B * exp(k2 * a / 2) / sqrt(1 + (k1 / k2) * exp(-2 * k1 *
    //     a));
    
    double B = (k1 / ((pow(cos(k2 * a / 2), 2)) +
                      k1 * (sin(k2 * a) / (2 * k2) + a / 2)));
    B = sqrt(B);
    double C = B * cos(k2 * a / 2) * exp(k1 * a / 2);

    auto func = [&](double x) -> double {
      if (x <= 0) {
        return C * exp(k1 * x) + solution;
      } else if (0 < x && x < a) {
        return B * cos(k2 * x) + solution;
      } else if (x >= a) {
        return C * exp(-k1 * x) + solution;
      }
    };

    std::vector<double> points = generatePoints(-a, a, 10000);
    std::vector<double> wavesFunc(points.size(), solution);

    std::transform(points.begin(), points.end(), wavesFunc.begin(),
                   func);

    plt::plot(points, wavesFunc);
  }

  // uncomment this to see Assymmetric function's levels
  /*
  std::vector<double> levelsCotan = generatePoints(0, a,
  amountOfNumbers); for(double solution : intersectionsRightCtg) {
    std::vector<double> numbers(levelsCotan.size(), solution);
    plt::plot(levelsCotan, numbers);
    plt::title("Assymetric wave functions");
  }
  */

  plt::show();
  plt::close();

  return 0;
}

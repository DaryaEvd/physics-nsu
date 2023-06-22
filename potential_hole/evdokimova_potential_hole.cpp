#include "matplotlibcpp.h"

#include <algorithm>
#include <cmath>
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

  plt::plot(E, rightPart);
  plt::plot(E, tg);
  plt::plot(E, ctg);

  plt::plot(E, xAxis);
  plt::show();

  return 0;
}

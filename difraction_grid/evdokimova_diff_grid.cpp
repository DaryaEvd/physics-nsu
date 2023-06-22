#include "matplotlibcpp.h"
#include <cmath>
#include <iostream>
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

double countSinc(double xPoints) {
  return std::sin(xPoints) / xPoints;
}

double countLeftMult(double lengthOfWave, double thetta, double a) {
  return countSinc(M_PI * a / lengthOfWave * std::sin(thetta));
}

double countRightMult(double lengthOfWave, double thetta, double d,
                      const int N) {
  double commonCoefficient =
      M_PI * d * std::sin(thetta) / lengthOfWave;

  double numerator = std::sin(N * commonCoefficient);
  double denominator = std::sin(commonCoefficient);

  return numerator / denominator;
}

double countIntensity(const int nGaps, double lengthOfWave,
                      double thetta, double a, double d, double I_0) {

  double leftPart = countLeftMult(lengthOfWave, thetta,
                                  a); // левый множитель в формуле
  double squareLeft = leftPart * leftPart;

  double rightPart = countRightMult(
      lengthOfWave, thetta, d, nGaps); // правый множитель в формуле
  double squareRight = rightPart * rightPart;

  return I_0 * squareLeft * squareRight;
}

void drawIntensity() {
  int nGaps = 10; // кол-во щелей
  double I_0 = 1; // интенсивность I_0

  // длина волн видимого света
  double lengthRedLight = 400;
  double lengthPurpleLight = 700;

  int m = 3; // порядок максимума

  const int a = 1500;
  const int d = 4000;

  double thetta = (m * lengthRedLight / d);
  // std::cout << "thetta = " << thetta << std::endl;

  int amountOfPoints = 50000;
  // координаты по Ox на графике
  // строим массив точек, от которых будем считать

  std::vector<double> xPoints =
      generatePoints(-thetta, thetta, amountOfPoints);

  std::vector<double> redLight;
  std::vector<double> purpleLight;

  for (double xCoord : xPoints) {
    redLight.push_back(
        countIntensity(nGaps, lengthRedLight, xCoord, a, d, I_0));
    purpleLight.push_back(
        countIntensity(nGaps, lengthPurpleLight, xCoord, a, d, I_0));
  }

  std::vector<double> xSinArray;
  for (double xCoord : xPoints) {
    xSinArray.push_back(std::sin(xCoord));
  }

  plt::title("Intensity");

  plt::plot(xSinArray, redLight, "red");
  plt::plot(xSinArray, purpleLight, "purple");
  plt::show();
}

int main() {
  drawIntensity();
  return 0;
}

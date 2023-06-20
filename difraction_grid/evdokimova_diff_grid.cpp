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

double countSinc(double x) { return std::sin(x) / x; }

double countLeftMult(double lengthOfWave, double thetta, double a) {
  return countSinc(M_PI * a / lengthOfWave * std::sin(thetta));
}

double countRightMult(double lengthOfWave, double thetta, double d,
                      int N) {
  double numerator =
      std::sin(N * M_PI * d / lengthOfWave * std::sin(thetta));
  double denominator =
      std::sin(M_PI * d / lengthOfWave * std::sin(thetta));

  return numerator / denominator;
}

double countIntensity(int nGaps, double lengthOfWave, double thetta,
                      double a, double d, double I_0) {

  double leftMult = countLeftMult(lengthOfWave, thetta, d); //левый множитель в формуле
  double squareLeftMult = leftMult * leftMult;

  double rightMult = countRightMult(lengthOfWave, thetta, d, nGaps); //правый множитель в формуле
  double squareRightMult = rightMult * rightMult;

  return I_0 * squareLeftMult * squareRightMult;
}

void drawIntensity() {
  int nGaps = 10; // кол-во щелей
  double I_0 = 1; // интенсивность I_0

  // длина волн видимого света
  double lengthRedLight = 400;
  double lengthPurpleLight = 700;

  int m = 1; // порядок максимума 

  double a = 0.001;
  int d = 1000;

  double thetta = m * lengthPurpleLight / d;
  // std::cout << "thetta = " << thetta << std::endl;

  int amountOfPoints = 50000;
  // координаты по Ox на графике
  // строим массив точек, от которых будем считать
  std::vector<double> xPoints = generatePoints( 
      -thetta, thetta,
      amountOfPoints); 

  // for (int i = 0; i < 10; i++) {
  //   std::cout << x.at(i)
  //             << " "; // посмотреть координаты (ну у первых 10 хотя б)
  // }
  // std::cout << std::endl;

  std::vector<double> redLight, purpleLight; //координаты по Oy на графике

  for (double xCoord: xPoints) {
    redLight.push_back(
        countIntensity(nGaps, lengthRedLight, xCoord, a, d, I_0));
    purpleLight.push_back(
        countIntensity(nGaps, lengthPurpleLight, xCoord, a, d, I_0));
  }

  plt::title("Intensity");
  plt::plot(xPoints, redLight, "red");
  plt::plot(xPoints, purpleLight, "purple");
 
  plt::show();
}

int main() {
  drawIntensity();
  return 0;
}

#include "../include/matplotlibcpp.h"
#include "constants.hpp"

#include <cmath>
#include <vector>

namespace plt = matplotlibcpp;

using namespace myConsts;

std::complex<double> countSpace(double x) {
  return std::exp((-x * x / (a * a)) + iCompl * kWaveNum * x);
}

double countRealSpatialDependce(double x) {
  return A * std::sqrt(M_PI) * countSpace(x).real();
}

double countImageSpatialDependence(double x) {
  return A * std::sqrt(M_PI) * countSpace(x).imag();
}

std::complex<double> countTime(double t) {
  return exp(iCompl * omega * t);
}

double countRealTimeDependence(double t) {
  return A * std::sqrt(M_PI) * countTime(t).real();
}

double countImageTimeDependence(double t) {
  return A * std::sqrt(M_PI) * countTime(t).imag();
}

void createTDSE(double time) {
  std::vector<double> xPrev, yPrev;
  std::vector<double> xNow, yNow;

  double step = 0.01;
  double bound = 1.5;

  for (double x = -bound; x <= bound; x += step) {
    double realSpacePrev = countRealSpatialDependce(x);
    xPrev.push_back(realSpacePrev);

    double imageSpacePrev = countImageSpatialDependence(x);
    yPrev.push_back(imageSpacePrev);

    double realTimeNow = countRealTimeDependence(time);
    xNow.push_back(realTimeNow);

    double imageTimeNow = countImageTimeDependence(time);
    yNow.push_back(imageTimeNow);
  }

  plt::plot(xPrev, yPrev, "red");
  plt::plot(xNow, yNow, "blue");
  plt::title("Time dependent Schrodinger Equation");
  plt::show();
  plt::close();
}

int main(int argc, char **argv) {
  if (argc != 2) {
    std::cout << "You need to enter time as argument to program"
              << std::endl;
    return 0;
  }

  double time = std::atof(argv[1]);

  createTDSE(time);

  return 0;
}

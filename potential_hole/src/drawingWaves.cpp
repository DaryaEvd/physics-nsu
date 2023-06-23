#include "matplotlibcpp.h"

#include "drawingWaves.hpp"

#include "calculations.hpp"
#include "coefficients.hpp"

#include <cmath> 
namespace plt = matplotlibcpp;

void drawSymmetricWaveFunction(std::vector<double> intersections,
                               const int h, const int m,
                               const int U_0, const int a) {
  for (double solution : intersections) {
    double k2 = sqrt(2 * m * (solution + U_0)) / h; // inside
    double k1 = sqrt(2 * m * abs(solution)) / h;    // outside

    double B = countSymmetricB(k1, k2, a);
    double C = countSymmetricC(k1, k2, a, B);

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

    double B = countAssymmetricB(k1, k2, a);
    double C = countAssymmetricC(k1, k2, a, B);

    std::vector<double> x = generatePoints(0, a, 10000);
    std::vector<double> waveFuncArray(x.size());

    for (size_t i = 0; i < x.size(); i++) {
      waveFuncArray[i] = assymmetricFunctionEquations(
          x[i], C, B, k1, k2, solution, a);
    }

    plt::plot(x, waveFuncArray);
  }
}
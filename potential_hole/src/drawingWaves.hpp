#pragma once

#include <iostream>
#include <vector>

void drawSymmetricWaveFunction(std::vector<double> intersections,
                               const int h, const int m,
                               const int U_0, const int a);

void drawAssymmetricWaveFunction(std::vector<double> intersections,
                                 const int h, const int m,
                                 const int U_0, const int a);

#pragma once

#include <vector>

std::vector<double> generatePoints(double start, double end,
                                   int amountOfNumbers);

double generateFunction(int level, double a, double m, double U_0,
                        double h);

#pragma once

#include <complex>

namespace myConsts {
const double hBar = 1;
const double kWaveNum = 1;
const double a = 1;

double A = std::sqrt(1 / a * std::sqrt(2 / M_PI));
double omega = (hBar * kWaveNum) * (hBar * kWaveNum) / 2 / hBar;
std::complex<double> iCompl(0.0, 1.0);
} // namespace myConsts
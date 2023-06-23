#include "consoleOutput.hpp"

#include <iomanip>
#include <iostream>

void printOutput(std::vector<double> intersections) {
  for (size_t i = 0; i < intersections.size(); i++) {
    std::cout << "#" << i + 1 << ": " << std::fixed
              << std::setprecision(7) << intersections[i]
              << std::endl;
  }
  std::cout << "========================================"
            << std::endl;
}
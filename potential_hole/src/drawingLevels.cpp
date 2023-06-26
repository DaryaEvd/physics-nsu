#include "matplotlibcpp.h"
 
namespace plt = matplotlibcpp;

void drawLevels(std::vector<double> levels,
                std::vector<double> intersections) {
  for (double solution : intersections) {
    std::vector<double> numbers(levels.size(), solution);
    plt::plot(levels, numbers);
  }
}

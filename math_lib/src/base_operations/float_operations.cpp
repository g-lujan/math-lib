#include "float_operations.h"
#include <cmath>

namespace floats {
  bool equal(float a, float b) { return abs(a - b) < EPSILON; }
} // namespace floats
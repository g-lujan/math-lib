#include <cmath>
#include "float_operations.h"
namespace floats {
	bool equal(float a, float b) { return abs(a - b) < EPSILON; }
 }
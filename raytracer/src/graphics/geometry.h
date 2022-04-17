#ifndef _GEOMETRY_H_
#define _GEOMETRY_H_

#include "../math/matrix.h"
#include "../math/float_operations.h"
#include "ray.h"
#include <array>
#include <algorithm>

Matrix<float, 4, 1> point3D(float x, float y, float z);
Matrix<float, 4, 1> vec3D(float x, float y, float z);
Ray3D ray3D(const float(&origin)[3][1], const float(&direction)[3][1]);

#endif
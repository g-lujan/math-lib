#ifndef _GEOMETRY_H_
#define _GEOMETRY_H_

#include "../math/matrix.h"
#include "../shapes/shape.h"
#include "../shapes/intersections.h"
#include "ray.h"

namespace Geometry {
	Matrix<float, 4, 1> point3D(float x, float y, float z);
	Matrix<float, 4, 1> vec3D(float x, float y, float z);
	Intersections intersections(const Ray3D&, const Shape&);
}

#endif
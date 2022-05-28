#include "geometry.h"

namespace Geometry {
    Matrix<float, 4, 1> point3D(float x, float y, float z) {
        return Matrix<float, 4, 1>({ { x }, {y}, {z}, {1} });
    }

    Matrix<float, 4, 1> vec3D(float x, float y, float z) {
        return Matrix<float, 4, 1>({ { x }, {y}, {z}, {0} });
    }

    Intersections intersections(const Ray3D& ray, const Shape& form) {
        return { form.intersections(ray), &form };
    }
}
#ifndef _RAY_H_
#define _RAY_H_

#include <vector>

#include "../math/matrix.h"
#include "../basic_shapes/sphere.h"
#include "geometry.h"

class Ray3D {
public:
	//friend Ray3D ray3D(const float(&origin)[3][1], const float(&direction)[3][1]);
	Ray3D(const float(&origin)[3][1], const float(&direction)[3][1]) {
		float originWithW[4][1];
		float directionWithW[4][1];
		for (std::size_t i = 0; i < 3; i++) {
			std::copy(std::begin(origin[i]), std::end(origin[i]), std::begin(originWithW[i]));
			std::copy(std::begin(direction[i]), std::end(direction[i]), std::begin(directionWithW[i]));
		}
		originWithW[3][0] = 1;
		origin_ = Matrix<float, 4, 1>(originWithW);
		directionWithW[3][0] = 0;
		direction_ = Matrix<float, 4, 1>(directionWithW);
	}

	std::vector<float> intersect(const Sphere& sphere);

	Matrix<float, 4, 1> origin() const { return origin_; }
	Matrix<float, 4, 1> direction() const { return direction_; }
	Matrix<float, 4, 1> propagate(float t) { return origin_ + direction_ * t; }

private:
	Ray3D(const float(&origin)[4][1], const float(&direction)[4][1]) : origin_(origin), direction_(direction) {}
	Matrix<float, 4, 1> origin_;
	Matrix<float, 4, 1> direction_;
};

#endif
#ifndef _RAY_H_
#define _RAY_H_

#include "../math/matrix.h"
#include "geometry.h"

class Ray3D {
public:
	friend Ray3D ray3D(const float(&origin)[3][1], const float(&direction)[3][1]);

	Matrix<float, 4, 1> origin() { return origin_; }
	Matrix<float, 4, 1> direction() { return direction_; }
	Matrix<float, 4, 1> propagate(float t){ return origin_ + direction_ * t; }

private:
	Ray3D(const float(&origin)[4][1], const float(&direction)[4][1]) : origin_(origin), direction_(direction) {}
	Matrix<float, 4, 1> origin_;
	Matrix<float, 4, 1> direction_;
};

#endif
#include "geometry.h"

Matrix<float, 4, 1> point3D(float x, float y, float z) {
    return Matrix<float, 4, 1> ({ { x }, {y}, {z}, {1} });
}

Matrix<float, 4, 1> vec3D(float x, float y, float z) {
    return Matrix<float, 4, 1>({ { x }, {y}, {z}, {0} });
}

Ray3D ray3D(const float(&origin)[3][1], const float(&direction)[3][1]) {
	float originWithW[4][1];
	float directionWithW[4][1];
	for (std::size_t i = 0; i < 3; i++) {
		std::copy(std::begin(origin[i]), std::end(origin[i]), std::begin(originWithW[i]));
		std::copy(std::begin(direction[i]), std::end(direction[i]), std::begin(directionWithW[i]));
	}
	originWithW[3][0] = 1;
	directionWithW[3][0] = 0;
	return Ray3D(originWithW, directionWithW);
}
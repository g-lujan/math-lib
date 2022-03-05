#include "transformation.h"

namespace Transformation {
	template <typename T>
	Matrix<T, 4, 4> translation3D(T x, T y, T z) {
		Matrix<T, 4, 4> translationMatrix({{1, 0, 0, x}, {0, 1, 0, y}, {0, 0, 1, z}, {0, 0, 0, 1}});
		return translationMatrix;
	}

	template <typename T>
	Matrix<T, 4, 4> scale3D(T x, T y, T z) {
		Matrix<T, 4, 4> scalingMatrix({ {x, 0, 0, 0}, {0, y, 0, 0}, {0, 0, z, 0}, {0, 0, 0, 1} });
		return scalingMatrix;
	}
	template<typename T>
	Matrix<T, 4, 4> rotX(T theta){
		return Matrix<T, 4, 4>({ {1, 0, 0, 0}, {0, std::cos(theta), -std::sin(theta), 0}, {0, std::sin(theta), std::cos(theta), 0}, {0, 0, 0, 1}});
	}
}
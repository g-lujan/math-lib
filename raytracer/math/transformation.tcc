#include "transformation.h"

namespace Transformation {
	template <typename T>
	Matrix<T, 4, 4> translation3D(T x, T y, T z) {
		Matrix<T, 4, 4> translationMatrix({{1, 0, 0, x}, {0, 1, 0, y}, {0, 0, 1, z}, {0, 0, 0, 1}});
		return translationMatrix;
	}
}
#include "transformation.h"

namespace Transformation {
	using std::cos;
	using std::sin;

	template <typename T>
	Matrix<T, 4, 4> translation3D(T x, T y, T z) {
		return Matrix<T, 4, 4>({ {1, 0, 0, x}, {0, 1, 0, y}, {0, 0, 1, z}, {0, 0, 0, 1} });
	}

	template <typename T>
	Matrix<T, 4, 4> scale3D(T x, T y, T z) {
		return Matrix<T, 4, 4>({ {x, 0, 0, 0}, {0, y, 0, 0}, {0, 0, z, 0}, {0, 0, 0, 1} });;
	}

	template<typename T>
	Matrix<T, 4, 4> rotX(T angle){
		return Matrix<T, 4, 4>({ {1, 0, 0, 0}, {0, cos(angle), -sin(angle), 0}, {0, sin(angle), cos(angle), 0}, {0, 0, 0, 1}});
	}

	template<typename T>
	Matrix<T, 4, 4> rotY(T angle) {
		return Matrix<T, 4, 4>({ {cos(angle), 0, sin(angle), 0}, {0, 1, 0, 0}, {-sin(angle), 0, cos(angle), 0}, {0, 0, 0, 1} });
	}

	template<typename T>
	Matrix<T, 4, 4> rotZ(T angle) {
		return Matrix<T, 4, 4>({ {cos(angle), -sin(angle), 0, 0}, {sin(angle), cos(angle), 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1} });
	}

	template<typename T>
	Matrix<T, 4, 4> shearing(T xy, T xz, T yx, T yz, T zx, T zy) {
		return Matrix<T, 4, 4>({ {1, xy, xz, 0}, {yx, 1, yz, 0}, {zx, zy, 1, 0}, {0, 0, 0, 1} });
	}
}
#pragma once

#ifndef _TRANSFORMATION_H_
#define _TRANSFORMATION_H_

#include "matrix.h"

namespace Transformation {
	template <typename T>
	Matrix<T, 4, 4> translation3D(T x, T y, T z);

	template <typename T>
	Matrix<T, 4, 4> scale3D(T x, T y, T z);

	template <typename T>
	Matrix<T, 4, 4> rotX(T angle);

	template <typename T>
	Matrix<T, 4, 4> rotY(T angle);

	template <typename T>
	Matrix<T, 4, 4> rotZ(T angle);
}

#include "transformation.tcc"

#endif
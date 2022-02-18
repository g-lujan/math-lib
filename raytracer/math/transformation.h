#pragma once

#ifndef _TRANSFORMATION_H_
#define _TRANSFORMATION_H_

#include "matrix.h"

namespace Transformation {
	template <typename T>
	Matrix<T, 4, 4> translation3D(T x, T y, T z);
}

#include "transformation.tcc"

#endif
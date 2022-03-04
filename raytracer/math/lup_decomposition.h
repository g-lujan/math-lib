#ifndef _LUP_DECOMPOSITION_
#define _LUP_DECOMPOSITION_

#include "matrix.h"
#include <optional> 

namespace LUP {
	template <typename T, std::size_t N> 
	struct Factors {
		Matrix<T, N, N> LU;
		Matrix<size_t, 1, N + 1> P;
	};

	template <typename T, std::size_t N> 
	std::optional<Factors<T, N>> factors(Matrix<T, N, N> m);
}

#include "lup_decomposition.tcc"

#endif // _LUP_DECOMPOSITION_

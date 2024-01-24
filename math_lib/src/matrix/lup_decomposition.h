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

  /*
  * This is quite expensive, as we need to make a copy of the input matrix M.
  * Maybe there is a better way to keep track of the matrix elements?
  */
  template <typename T, std::size_t N>
  std::optional<Factors<T, N>> factors(Matrix<T, N, N> m);
} // namespace LUP

#include "lup_decomposition.tcc"

#endif // _LUP_DECOMPOSITION_

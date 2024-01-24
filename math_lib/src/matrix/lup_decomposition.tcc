#include "lup_decomposition.h"

namespace LUP {

  template <typename T, size_t N>
  static void decompose(Matrix<T, N, N> &m, const size_t diag);


  template <typename T, size_t N>
  std::optional<Factors<T, N>> factors(Matrix<T, N, N> m)
  {
    static_assert(std::is_floating_point_v<T>, "LUP factors should be of floating point types");

    Matrix<size_t, 1, N + 1> P;
    for (size_t col = 0; col <= N; col++) {
      P(0, col) = col;
    }


    for (size_t diag = 0; diag < N; diag++) {
      /* the line which contains the max abs value in the column starting at diag */
      size_t lineOfMaxInCol = diag;
      for (size_t line = diag + 1; line < N; ++line) {
        if (std::abs(m(line, diag)) > std::abs(m(lineOfMaxInCol, diag))) {
          lineOfMaxInCol = line;
        }
      }

      if (std::abs(m(lineOfMaxInCol, diag)) < floats::EPSILON) {
        return std::nullopt; // can't decompose, matrix is degenerate
      }

      /*
      * the pivots should be ordered in a way that no element bigger than it is below it
      * in order to improve stability
      */
      if (lineOfMaxInCol != diag) {
        // pivoting P
        std::swap(P(0, diag), P(0, lineOfMaxInCol));
        // pivoting the matrix
        m.swapRows(diag, lineOfMaxInCol);
        // counting pivots starting from N (for determinant)
        P(0, N)++;
      }
      decompose(m, diag);
    }
    return Factors<T, N>{m, P}; // decomposition done
  }



  template <typename T, size_t N>
  static void decompose(Matrix<T, N, N> &m, const size_t diag)
  {
    for (size_t line = diag + 1; line < N; line++) {
      /*
       * m(line, diag) will keep the value of the divisions we applied
       * ie: [3,2,1]
       *     [1,2,5] - L1*1/3 => m(1,0) = 1/3
       *     [2,0,1] - L1*2/3 => m(2,0) = 2/3
       * those divisions are the Lower matrix
       */
      m(line, diag) /= m(diag, diag);
      for (size_t col = diag + 1; col < N; col++) {
        m(line, col) -= m(line, diag) * m(diag, col);
      }
    }
  }
} // namespace LUP
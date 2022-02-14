#include "lup_decomposition.h"

namespace LUP {
	template <typename T, size_t N>
	std::optional<Factors<T, N>> decompose(Matrix<T, N, N> m) {
		Matrix<size_t, 1, N + 1> P;
		for (size_t i = 0; i <= N; i++) {
			P(0, i) = i;
		}

		for (size_t col = 0; col < N; col++) {
			const size_t lineOfMaxInColBelowDiag = findLineOfMaxValueInColBelowDiag(m, col);
			if (std::abs(m(lineOfMaxInColBelowDiag, col)) < floats::EPSILON) {
				return std::nullopt; // can't decompose, matrix is degenerate
			}
			if (lineOfMaxInColBelowDiag != col) {
				pivot(lineOfMaxInColBelowDiag, col, P, m);
			}
			doDecompose(m, col);
		}
		return Factors<T, N>{m, P}; // decomposition done
	}

	template<typename T, size_t N>
	static size_t findLineOfMaxValueInColBelowDiag(Matrix<T, N, N>& m, const size_t col)
	{
		size_t lineOfMaxAbsValue = col;
		for (size_t k = col + 1; k < N; k++) {
			if (std::abs(m(k, col)) > std::abs(m(lineOfMaxAbsValue, col))) {
				lineOfMaxAbsValue = k;
			}
		}
		return lineOfMaxAbsValue;
	}

	template<typename T, size_t N>
	static void pivot(const size_t lineOfMaxInColBelowDiag, const size_t col, Matrix<size_t, 1Ui64, N + (1)>& P, Matrix<T, N, N>& m)
	{
		// pivoting P
		std::swap(P(0, col), P(0, lineOfMaxInColBelowDiag));
		// pivoting the matrix
		m.swapRows(col, lineOfMaxInColBelowDiag);
		// counting pivots starting from N (for determinant)
		P(0, N)++;
	}

	template<typename T, size_t N>
	static void doDecompose(Matrix<T, N, N>& m, const size_t col)
	{
		for (size_t j = col + 1; j < N; j++) {
			m(j, col) /= m(col, col);
			for (size_t k = col + 1; k < N; k++) {
				m(j, k) -= m(j, col) * m(col, k);
			}
		}
	}
}
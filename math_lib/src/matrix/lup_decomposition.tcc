#include "lup_decomposition.h"

namespace LUP {
	template<typename T, size_t N> static size_t findLineOfMaxValueInColFromDiagToEnd(Matrix<T, N, N>& m, const size_t diag);
	template<typename T, size_t N> static void pivot(const size_t lineOfMaxInColBelowDiag, const size_t col, Matrix<size_t, 1Ui64, N + (1)>& P, Matrix<T, N, N>& m);
	template<typename T, size_t N>	static void decompose(Matrix<T, N, N>& m, const size_t diag);

	template <typename T, size_t N>
	std::optional<Factors<T, N>> factors(Matrix<T, N, N> m) {
		static_assert(std::is_floating_point_v<T>, "LUP factors should be of floating point types");
		Matrix<size_t, 1, N + 1> P;
		for (size_t i = 0; i <= N; i++) {
			P(0, i) = i;
		}

		for (size_t diag = 0; diag < N; diag++) {
			const size_t lineOfMaxInColFromDiagToEnd = findLineOfMaxValueInColFromDiagToEnd(m, diag);
			if (std::abs(m(lineOfMaxInColFromDiagToEnd, diag)) < floats::EPSILON) {
				return std::nullopt; // can't decompose, matrix is degenerate
			}
			if (lineOfMaxInColFromDiagToEnd != diag) {
				// the pivot should always be the biggest element for stability
				pivot(lineOfMaxInColFromDiagToEnd, diag, P, m);
			}
			decompose(m, diag);
		}
		return Factors<T,N>{m, P}; // decomposition done
	}

	template<typename T, size_t N>
	static size_t findLineOfMaxValueInColFromDiagToEnd(Matrix<T, N, N>& m, const size_t diag)
	{
		size_t lineOfMaxAbsValue = diag;
		for (size_t k = diag + 1; k < N; k++) {
			if (std::abs(m(k, diag)) > std::abs(m(lineOfMaxAbsValue, diag))) {
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
	static void decompose(Matrix<T, N, N>& m, const size_t diag)
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
}
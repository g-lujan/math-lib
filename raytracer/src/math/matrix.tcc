#include "matrix.h"
#include <iostream>
#include <sstream>
#include <optional> 
#include "float_operations.h"
#include "lup_decomposition.h"

using std::size_t;

template <typename T, typename U, size_t TRows, size_t TCols, size_t TCommon>
Matrix<std::common_type_t<T,U>, TRows, TCols> operator*(const Matrix<T, TRows, TCommon>& lhs, const Matrix<U, TCommon, TCols>& rhs) {
	Matrix<std::common_type_t<T, U>, TRows, TCols> productResult;
	for (size_t i = 0; i < TRows; i++) {
		for (size_t j = 0; j < TCommon; j++) {
			for (size_t k = 0; k < TCols; k++) {
				productResult(i, k) += lhs(i, j) * rhs(j, k);
			}
		}
	}
	return productResult;
}

template <typename T, typename U, size_t TRows, size_t TCols>
Matrix<std::common_type_t<T, U>, TRows, TCols> operator*(const Matrix<T, TRows, TCols>& lhs, const U& rhs) {
	Matrix<std::common_type_t<T, U>, TRows, TCols> productResult;
	for (size_t i = 0; i < TRows; i++) {
		for (size_t j = 0; j < TCols; j++) {
			productResult(i, j) += lhs(i, j) * rhs;
		}
	}
	return productResult;
}

template <typename T, typename U, size_t TRows, size_t TCols>
Matrix<std::common_type_t<T, U>, TRows, TCols> operator*(const U& rhs, const Matrix<T, TRows, TCols>& lhs) {
	return lhs * rhs;
}

template <typename T, size_t TRows, size_t TCols>
template <typename U, size_t TRowsOther, size_t TColsOther>
bool Matrix<T, TRows, TCols>::operator==(const Matrix<U, TRowsOther, TColsOther>& rhs){
	if (TRows != TRowsOther || TCols != TColsOther) {
		return false;
	}
	for (int i = 0; i < TRows; i++) {
		for (int j = 0; j < TCols; j++) {
			if (!floats::equal(data_[i][j], rhs(i,j))) {
				return false;
			}
		}
	}
	return true;
}


template <typename T, typename U, size_t TRows, size_t TCols> Matrix<std::common_type_t<T, U>, TRows, TCols>
operator+(const Matrix<T, TRows, TCols>& m1, const Matrix<U, TRows, TCols>& m2) {
	Matrix<std::common_type_t<T, U>, TRows, TCols> sumResult;
	for (size_t i = 0; i < TRows; i++) {
		for (size_t j = 0; j < TCols; j++) {
			sumResult(i, j) = m1(i, j) + m2(i, j);
		}
	}
	return sumResult;
}

template <typename T, size_t TRows, size_t TCols> 
std::ostream& operator<<(std::ostream& os, Matrix<T, TRows, TCols> const& m) {
	std::stringstream matrixFields;
	for (size_t i = 0; i < TRows; i++) {
		for (size_t j = 0; j < TCols; j++) {
			matrixFields << m(i, j) << " ";
		}
		matrixFields << std::endl;
	}
	return os << matrixFields.str();
}

template <typename T, size_t TRows, size_t TCols> Matrix<T, TCols, TRows> 
Matrix<T, TRows, TCols>::transpose() {
	Matrix<T, TCols, TRows> transposed;
	for (size_t i = 0; i < TRows; i++) {
		for (size_t j = 0; j < TCols; j++) {
			transposed(j, i) = data_[i][j];
		}
	}
	return transposed;
}

template <typename T, size_t TRows, size_t TCols>
Matrix<T, TCols - 1, TRows - 1> Matrix<T, TRows, TCols>::copyWithout(unsigned int rowToDelete, unsigned int colToDelete) {
	Matrix<T, TCols - 1, TRows - 1> sub;
	for (size_t i = 0; i < TRows - 1; i++) {
		for (size_t j = 0; j < TCols - 1; j++) {
			sub(i, j) = data_[i < rowToDelete ? i : i + 1][j < colToDelete ? j : j + 1];
		}
	}
	return sub;
}


template <typename T, size_t N>
T det(const Matrix<T, N, N>& m) {
	const std::optional<LUP::Factors<T,N>> factors = LUP::factors(m);
	if (!factors.has_value()) {
		return 0.0;
	}
	T det = 1;
	for (size_t i = 0; i < N; i++) {
		det *= factors->LU(i, i);
	}
	return (factors->P(0, N) - N) % 2 == 0 ? det : -det;
}

template <typename T, size_t N>
bool invert(Matrix<T, N, N>& m) {
	static_assert(std::is_floating_point_v<T>, "A Matrix of floating point values is required for invertion.");
	if (!isInvertible(m)) {
		return false;
	}
	const std::optional<LUP::Factors<T,N>> LUPfactors = LUP::factors(m);
	if (!LUPfactors.has_value()) {
		return false;
	}
	/*
	* A*inv(A) = I => LU*inv(A) = I
	* let: (1): U*inv(A) = X => (2): L*X = I
	* first solve (2) with forward substitution to find X,
	* than use X in (1) to find inv(A) with back substitution
	*/
	for (size_t col = 0; col < N; col++) {
		forwardSubstitution(m, col, LUPfactors.value());
		backSubstitution(m, col, LUPfactors.value());
	}
	return true;
}

template<typename T, size_t N>
static void forwardSubstitution(Matrix<T, N, N>& m, const size_t col, const LUP::Factors<T,N>& factors)
{
	// solve for X in place. after a run of this forwardSubstitution, the col in the original matrix
	// will have the values of the same col of the solution X
	for (int line = 0; line < N; line++) {
		// the right side (identity), considering the correction of the previous permutations registred on P
		m(line, col) = (factors.P(0, line) == col ? 1.0f : 0.0f);
		for (int k = 0; k < line; k++) {
			/*
			 * m(line, col) starts as the identity position and we iterate solving the problem, using previous results
			 * ie: 
			 *     L_00 * X_00 = I_00                               => X_00 = 1/L_00
			 *     L_10 * X_00 + L_11 * X_10 = I_10                 => X_10 = (I_10 - (L_10 * X_00))/L_11
			 *     L_20 * X_00 + L_21 * X_10 + L_22 * X_20 == I_20  => X_20 = (I_20 - (L_20 * X_00 + L_21 * X_10))/L_22
			 * note: the divisions above (by L_00, by L_11, by L_22, ...) are postponed to the end, to allow us to compute a division
			 * only once for every element.
			 */
			m(line, col) -= factors.LU(line, k) * m(k, col);
		}
	}
}

template<typename T, size_t N>
static void backSubstitution(Matrix<T, N, N>& m, const size_t col, const LUP::Factors<T,N>& factors)
{
	// solve for inv(A) in place. after a run of this backSubstitution, the col in the original matrix
	// will have the values of the same col of the solution inv(A)
	for (int line = N - 1; line >= 0; line--) {
		for (int k = line + 1; k < N; k++) {
			// notice how we calculate the same way as the forward, but here the m(line, col) is
			// already the X
			m(line, col) -= factors.LU(line, k) * m(k, col);
		}
		// postponed division
		m(line, col) /= factors.LU(line, line);
	}
}

template <typename T, size_t N>
static bool isInvertible(const Matrix<T, N, N>& m) {
	return !(floats::equal(det(m), 0.000000000f));
}
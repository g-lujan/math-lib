#include "matrix.h"
#include <iostream>
#include <sstream>
#include <optional> 
#include "float_operations.h"
#include "lup_decomposition.h"

using std::size_t;

template <typename T, size_t TRows, size_t TCols, size_t TCommon>
Matrix<T, TRows, TCols> operator*(const Matrix<T, TRows, TCommon>& lhs, const Matrix<T, TCommon, TCols>& rhs) {
	Matrix<T, TRows, TCols> productResult;
	for (size_t i = 0; i < TRows; i++) {
		for (size_t j = 0; j < TCommon; j++) {
			for (size_t k = 0; k < TCols; k++) {
				productResult(i, k) += lhs(i, j) * rhs(j, k);
			}
		}
	}
	return productResult;
}

template <typename T, size_t TRows, size_t TCols, size_t TRowsOther, size_t TColsOther>
bool operator==(const Matrix<T, TRows, TCols>& lhs, const Matrix<T, TRowsOther, TColsOther>& rhs) {
	if (TRows != TRowsOther || TCols != TColsOther) {
		return false;
	}
	for (int i = 0; i < TRows; i++) {
		for (int j = 0; j < TCols; j++) {
			if (!floats::equal(lhs.data_[i][j], rhs.data_[i][j])) {
				return false;
			}
		}
	}
	return true;
}

template <typename T, size_t TRows, size_t TCols> Matrix<T, TRows, TCols> operator+(const Matrix<T, TRows, TCols>& m1, const Matrix<T, TRows, TCols>& m2) {
	Matrix<T, TRows, TCols> sumResult;
	for (size_t i = 0; i < TRows; i++) {
		for (size_t j = 0; j < TCols; j++) {
			sumResult(i, j) = m1(i, j) + m2(i, j);
		}
	}
	return sumResult;
}

template <typename T, size_t TRows, size_t TCols> std::ostream& operator<<(std::ostream& os, Matrix<T, TRows, TCols> const& m) {
	std::stringstream matrixFields;
	for (size_t i = 0; i < TRows; i++) {
		for (size_t j = 0; j < TCols; j++) {
			matrixFields << m(i, j) << " ";
		}
		matrixFields << std::endl;
	}
	return os << matrixFields.str();
}

template <typename T, size_t TRows, size_t TCols> Matrix<T, TCols, TRows> Matrix<T, TRows, TCols>::transpose() {
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
	if (auto factors = LUP::decompose(m)) {
		T det = 1;
		for (size_t i = 0; i < N; i++) {
			det *= factors->LU(i, i);
		}
		return (factors->P(0, N) - N) % 2 == 0 ? det : -det;
	}
	return 0.0;
}

template <typename T, size_t N>
bool invert(Matrix<T, N, N>& m) {
	if (!isInvertible(m)) {
		return false;
	}
	const std::optional<LUP::Factors<T, N>> LUPfactors = LUP::decompose(m);
	if (!LUPfactors.has_value()) {
		return false;
	}

	// considering that A*invert(A) == I and that A=P*L*U
	// => A*x = [1,0,0,...,0], where x is the first col of invert(A)
	// => A*y = [0,1,0,...,0], where y is the second col of invert(A)
	// and so on
	for (size_t col = 0; col < N; col++) {
		forwardSubstitution(m, col, LUPfactors.value());
		backSubstitution(m, col, LUPfactors.value());
	}
	return true;
}

template<typename T, size_t N>
static void forwardSubstitution(Matrix<T, N, N>& m, const size_t col, const LUP::Factors<T, N>& factors)
{
	for (int line = 0; line < N; line++) {
		// the right side (identity)
		m(line, col) = (factors.P(0, line) == col ? 1.0f : 0.0f);
		// le dnv sobre lu decomposition...
		for (int k = 0; k < line; k++) {
			m(line, col) -= factors.LU(line, k) * m(k, col);
		}
	}
}

template<typename T, size_t N>
static void backSubstitution(Matrix<T, N, N>& m, const size_t col, const LUP::Factors<T, N>& factors)
{
	for (int line = N - 1; line >= 0; line--) {
		for (int k = line + 1; k < N; k++)
			m(line, col) -= factors.LU(line, k) * m(k, col);
		m(line, col) /= factors.LU(line, line);
	}
}

template <typename T, size_t N>
static bool isInvertible(const Matrix<T, N, N>& m) {
	return !(floats::equal(det(m), 0.000000000f));
}
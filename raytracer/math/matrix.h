#pragma once

#ifndef _MATRIX_H_
#define _MATRIX_H_

#include <algorithm>
#include <array>
#include <cassert>
#include <cmath>
#include <optional>

template <typename T,std::size_t N> struct LUPFactors;

template <typename T, std::size_t TRows, std::size_t TCols> class Matrix {
public:
    Matrix() : data_({ {} }) {};

    template <std::size_t N, std::size_t M> 
    Matrix(const T(&data)[N][M]) {
        static_assert(N == TRows, "Invalid number of rows.");
        static_assert(M == TCols, "Invalid number of columns.");
        for (std::size_t i = 0; i < TRows; i++) {
            std::copy(std::begin(data[i]), std::end(data[i]), std::begin(data_[i]));
        }
    }

    std::size_t rows() { return TRows; };

    void swapRows(std::size_t i, std::size_t j) { std::swap(data_[i], data_[j]); }

    std::size_t cols() { return TCols; };

    bool isSquare() { return TRows == TCols; }

    T& operator()(std::size_t i, std::size_t j) { return data_[i][j]; }

    const T& operator()(std::size_t i, std::size_t j) const { return data_[i][j]; }

    template <typename T, std::size_t TRows1, std::size_t TCols1, std::size_t TRows2, std::size_t TCols2>
    friend bool operator==(const Matrix<T,TRows1, TCols1>& lhs, const Matrix<T,TRows2, TCols2>& rhs);

    template <typename T, std::size_t TRowsOther, std::size_t TColsOther> friend bool operator!=(const Matrix& lhs, const Matrix<T,TRowsOther, TColsOther>& rhs) {
        return !(lhs == rhs);
    }

    // TODO
    template <std::size_t N> void transform(std::initializer_list<Matrix<T,N, N>>& transformations);

    Matrix<T, TCols, TRows> transpose();

    Matrix<T, TCols - 1, TRows - 1> copyWithout(unsigned int row_to_delete, unsigned int col_to_delete);

private:
    std::array<std::array<T, TCols>, TRows> data_;
};

template <typename T, std::size_t N>
T det(const Matrix<T,N, N>& m);

template <typename T, std::size_t N> 
std::optional<Matrix<T,N, N>> invert(const Matrix<T,N, N>& m);

#include "matrix.tcc"

#endif

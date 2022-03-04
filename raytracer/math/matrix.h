#pragma once

#ifndef _MATRIX_H_
#define _MATRIX_H_

#include <algorithm>
#include <array>
#include <cassert>
#include <cmath>
#include <optional>


template <typename T, std::size_t TRows, std::size_t TCols>
class Matrix {

    static_assert(std::is_arithmetic_v<T>, "Matrix should be of arithmetic types");

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

    template <typename U, size_t TRowsOther, size_t TColsOther>
    bool operator==(const Matrix<U, TRowsOther, TColsOther>& rhs);

    template <typename U, std::size_t TRowsOther, std::size_t TColsOther> 
    bool operator!=(const Matrix<U,TRowsOther, TColsOther>& rhs) {
        return !(*this == rhs);
    }

    Matrix<T, TCols, TRows> transpose();

    Matrix<T, TCols - 1, TRows - 1> copyWithout(unsigned int rowToDelete, unsigned int colToDelete);

private:
    std::array<std::array<T, TCols>, TRows> data_;
};

template <typename T, std::size_t N>
T det(const Matrix<T,N, N>& m);

template <typename T, std::size_t N>
bool invert(const Matrix<T, N, N>& m);

#include "matrix.tcc"

#endif
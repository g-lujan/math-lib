#pragma once

#ifndef _MATRIX_H_
#define _MATRIX_H_

#include <algorithm>
#include <vector>
#include <cassert>
#include <cmath>
#include <optional>
#include <string>

template <typename T, std::size_t TRows, std::size_t TCols>
class Matrix {

  static_assert(std::is_arithmetic_v<T>, "Matrix should be of arithmetic types");

public:
  Matrix() : data_(TRows, std::vector<T>(TCols, 0)) {};

  template <std::size_t N, std::size_t M>
  Matrix(const T (&data)[N][M]) : data_(TRows, std::vector<T>(TCols))
  {
    static_assert(N == TRows, "Invalid number of rows.");
    static_assert(M == TCols, "Invalid number of columns.");
    
    for (std::size_t i = 0; i < TRows; i++) {
      for (std::size_t j = 0; j < TCols; j++) {
        data_[i][j] = data[i][j];
      }
    }
  }

  inline std::size_t rows() const { return TRows; };

  inline void swapRows(std::size_t i, std::size_t j) { std::swap(data_[i], data_[j]); }

  inline std::size_t cols() const { return TCols; };

  inline bool isSquare() const { return TRows == TCols; }

  T &operator()(std::size_t i, std::size_t j) { return data_[i][j]; }

  const T &operator()(std::size_t i, std::size_t j) const { return data_[i][j]; }

  template <typename U, size_t TRowsOther, size_t TColsOther>
  bool operator==(const Matrix<U, TRowsOther, TColsOther> &rhs) const;

  template <typename U, std::size_t TRowsOther, std::size_t TColsOther>
  bool operator!=(const Matrix<U, TRowsOther, TColsOther> &rhs) const
  {
    return !(*this == rhs);
  }

  Matrix<T, TCols, TRows> transpose();

  Matrix<T, TCols - 1, TRows - 1> copyWithout(unsigned int rowToDelete, unsigned int colToDelete);

private:
  std::vector<std::vector<T>> data_;
};

template <typename T, std::size_t N>
T det(const Matrix<T, N, N> &m);

template <typename T, std::size_t N>
bool invert(const Matrix<T, N, N> &m);

template <typename T, std::size_t TRows, std::size_t TCols>
Matrix<float, TRows, TCols> loadtxt(const std::string &path);

#include "matrix.tcc"

#endif
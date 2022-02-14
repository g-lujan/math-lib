#define BOOST_TEST_MODULE Matrix
#include "matrix.h"
#include "lup_decomposition.h"
#include <boost/test/included/unit_test.hpp>
#include <iostream>

// Nota: voce ta cagando para comparacao float em varios testes

BOOST_AUTO_TEST_CASE(test_inspect_4x4_matrix) {
    Matrix<float,4, 4> M({ {1, 2, 3, 4}, {5.5f, 6.5f, 7.5f, 8.5f}, {9, 10, 11, 12}, {13.5f, 14.5f, 15.5f, 16.5f} });
    BOOST_CHECK(M(0, 0) == 1);
    BOOST_CHECK(M(0, 3) == 4);
    BOOST_CHECK(M(1, 0) == 5.5);
    BOOST_CHECK(M(1, 2) == 7.5);
    BOOST_CHECK(M(2, 2) == 11);
    BOOST_CHECK(M(3, 0) == 13.5);
    BOOST_CHECK(M(3, 2) == 15.5);
    BOOST_CHECK(M.isSquare());
}

BOOST_AUTO_TEST_CASE(test_inspect_2x2_matrix) {
    Matrix<float, 2, 2> M({ {-3, 5}, {1, -2} });
    BOOST_CHECK(M(0, 0) == -3);
    BOOST_CHECK(M(0, 1) == 5);
    BOOST_CHECK(M(1, 0) == 1);
    BOOST_CHECK(M(1, 1) == -2);
    BOOST_CHECK(M.isSquare());
}

BOOST_AUTO_TEST_CASE(test_inspect_2x3_matrix) {
    Matrix<float, 2, 3> M({ {-3, 5, 2}, {1, -2, 8} });
    BOOST_CHECK(M(0, 0) == -3);
    BOOST_CHECK(M(0, 1) == 5);
    BOOST_CHECK(M(0, 2) == 2);
    BOOST_CHECK(M(1, 0) == 1);
    BOOST_CHECK(M(1, 1) == -2);
    BOOST_CHECK(M(1, 2) == 8);
    BOOST_CHECK(!M.isSquare());
}

BOOST_AUTO_TEST_CASE(test_inspect_3x3_matrix) {
    Matrix<float, 3, 3> M({ {-3, 5, 0}, {1, -2, -7}, {0, 1, 1} });
    BOOST_CHECK(M(0, 0) == -3);
    BOOST_CHECK(M(0, 1) == 5);
    BOOST_CHECK(M(0, 2) == 0);
    BOOST_CHECK(M(1, 0) == 1);
    BOOST_CHECK(M(1, 1) == -2);
    BOOST_CHECK(M(1, 2) == -7);
    BOOST_CHECK(M(2, 0) == 0);
    BOOST_CHECK(M(2, 1) == 1);
    BOOST_CHECK(M(2, 2) == 1);
    BOOST_CHECK(M.isSquare());
}

BOOST_AUTO_TEST_CASE(test_empty_matrix) {
    Matrix<float, 0, 0> M;
    BOOST_CHECK(M.rows() == 0);
    BOOST_CHECK(M.cols() == 0);
}

BOOST_AUTO_TEST_CASE(test_compare_equal_matrices) {
    Matrix<float, 2, 2> A({ {2.2f, 1.3f}, {2.4f, 1.9f} });
    Matrix<float, 2, 2> B({ {2.2f, 1.3f}, {2.4f, 1.9f} });
    BOOST_CHECK(A == B);
}


BOOST_AUTO_TEST_CASE(test_compare_different_matrices) {
    Matrix<float, 2, 2> A({ {2.2f, 1.3f}, {2.5f, 1.9f} });
    Matrix<float, 2, 2> B({ {2.2f, 1.3f}, {2.4f, 1.9f} });
    Matrix<float, 3, 3> C({ {1, 2, 3}, {3, 4, 5}, {6, 7, 8} });
    BOOST_CHECK(A != B);
    BOOST_CHECK(A != C);
}

BOOST_AUTO_TEST_CASE(test_compare_different_matrices_with_similar_parts) {
    Matrix<float, 2, 2> A({ {2.2f, 1.3f}, {2.5f, 1.9f} });
    Matrix<float, 2, 3> B({ {2.2f, 1.3f, 1.0f}, {2.5f, 1.9f, 0.0f} });
    BOOST_CHECK(A != B);
    BOOST_CHECK(B != A);
    Matrix<float, 1, 2> C({ {2.2f, 1.3f} });
    BOOST_CHECK(A != C);
    BOOST_CHECK(C != A);
}

BOOST_AUTO_TEST_CASE(test_commutativity_of_equal_operator) {
    Matrix<float, 3, 3> A_1({ {1, 5, 9}, {-3, 2, -1}, {10, 99, 2} });
    Matrix<float, 3, 3> A_2({ {1, 5, 9}, {-3, 2, -1}, {10, 99, 2} });
    Matrix<float, 3, 3> B({ {1, 5, 8}, {-3, 2, -1}, {10, 99, 2} });
    BOOST_CHECK(A_1 == A_2);
    BOOST_CHECK(A_2 == A_1);
    BOOST_CHECK(A_1 != B);
    BOOST_CHECK(B != A_1);
}

BOOST_AUTO_TEST_CASE(test_adding_matrices) {
    Matrix<float, 2, 2> expected({ {2.2f, 1.3f}, {2.4f, 1.9f} });
    Matrix<float, 2, 2> A({ {1.5f, 0.8f}, {1.8f, 2.7f} });
    Matrix<float, 2, 2> B({ {0.7f, 0.5f}, {0.6f, -0.8f} });
    auto result = A + B;
    BOOST_CHECK(expected == result);
}

BOOST_AUTO_TEST_CASE(test_multiplying_4x4_matrices) {
    Matrix<float, 4, 4> A({ {1, 2, 3, 4}, {5, 6, 7, 8}, {9, 8, 7, 6}, {5, 4, 3, 2} });
    Matrix<float, 4, 4> B({ {-2, 1, 2, 3}, {3, 2, 1, -1}, {4, 3, 6, 5}, {1, 2, 7, 8} });
    Matrix<float, 4, 4> expected({ {20, 22, 50, 48}, {44, 54, 114, 108}, {40, 58, 110, 102}, {16, 26, 46, 42} });
    BOOST_CHECK(expected == (A * B));
}

BOOST_AUTO_TEST_CASE(test_multiplying_matrices_different_dimensions) {
    Matrix<float, 1, 3> A({ {1, 2, 3} });
    Matrix<float, 3, 2> B({ {2, 3}, {1, -1}, {6, 5} });
    Matrix<float, 1, 2> expected({ {22, 16} });
    BOOST_CHECK(expected == A * B);
}

BOOST_AUTO_TEST_CASE(test_direct_value_of_multiplication) {
    Matrix<float, 1, 3> A({ {1, 2, 3} });
    Matrix<float, 3, 2> B({ {2, 3}, {1, -1}, {6, 5} });
    Matrix<float, 1, 2> expected({ {22, 16} });
    auto AB = A * B;
    BOOST_CHECK(expected == AB);
    BOOST_CHECK(expected == (A * B));
    BOOST_CHECK(AB == (A * B));
}

BOOST_AUTO_TEST_CASE(test_invalid_matrix_validation) { Matrix<float, 2, 3> A({ {1.5f, 0.8f, 0.0f}, {1.8f, 2.7f, 5.6f} }); }

BOOST_AUTO_TEST_CASE(test_valid_matrix_validation) { Matrix<float, 2, 2> A({ {1.5f, 0.8f}, {1.8f, 2.7f} }); }

BOOST_AUTO_TEST_CASE(test_transpose_square_matrix) {
    Matrix<float, 4, 4> A({ {1, 2, 0, 0}, {0, 1, 3, 0}, {2, 0, 1, 0}, {9, 0, 0, 1} });
    Matrix<float, 4, 4> expected({ {1, 0, 2, 9}, {2, 1, 0, 0}, {0, 3, 1, 0}, {0, 0, 0, 1} });
    BOOST_CHECK(A.transpose() == expected);
}

BOOST_AUTO_TEST_CASE(test_transpose_matrix) {
    Matrix<float, 3, 2> A({ {1, 2}, {0, 1}, {2, 0} });
    Matrix<float, 2, 3> expected({ {1, 0, 2}, {2, 1, 0} });
    BOOST_CHECK(A.rows() == 3 && A.cols() == 2);
    auto A_transposed = A.transpose();
    BOOST_CHECK(A_transposed.rows() == 2 && A_transposed.cols() == 3);
    BOOST_CHECK(A_transposed == expected);
}

BOOST_AUTO_TEST_CASE(test_determinant_matrix_2x2) {
    Matrix<float, 2, 2> A({ {1, 5}, {-3, 2} });
    BOOST_CHECK(det(A) == 17);
}

BOOST_AUTO_TEST_CASE(test_submatrices_of_2x2) {
    Matrix<float, 2, 2> A({ {1, 5}, {-3, 2} });
    Matrix<float, 1, 1> element_1x1({ {2} });
    BOOST_CHECK(A.copyWithout(0, 0) == element_1x1);
    Matrix<float, 1, 1> element_0x0({ {1} });
    BOOST_CHECK(A.copyWithout(1, 1) == element_0x0);
    Matrix<float, 1, 1> element_1x0({ {-3} });
    BOOST_CHECK(A.copyWithout(0, 1) == element_1x0);
    Matrix<float, 1, 1> element_0x1({ {5} });
    BOOST_CHECK(A.copyWithout(1, 0) == element_0x1);
}

BOOST_AUTO_TEST_CASE(test_submatrices_of_3x3) {
    Matrix<float, 3, 3> A({ {1, 5, 9}, {-3, 2, -1}, {10, 99, 2} });
    Matrix<float, 2, 2> submatrix_without_0x0({ {2, -1}, {99, 2} });
    BOOST_CHECK(A.copyWithout(0, 0) == submatrix_without_0x0);
    Matrix<float, 2, 2> submatrix_without_0x1({ {-3, -1}, {10, 2} });
    BOOST_CHECK(A.copyWithout(0, 1) == submatrix_without_0x1);
    Matrix<float, 2, 2> submatrix_without_0x2({ {-3, 2}, {10, 99} });
    BOOST_CHECK(A.copyWithout(0, 2) == submatrix_without_0x2);
    Matrix<float, 2, 2> submatrix_without_1x0({ {5, 9}, {99, 2} });
    BOOST_CHECK(A.copyWithout(1, 0) == submatrix_without_1x0);
    Matrix<float, 2, 2> submatrix_without_1x1({ {1, 9}, {10, 2} });
    BOOST_CHECK(A.copyWithout(1, 1) == submatrix_without_1x1);
    Matrix<float, 2, 2> submatrix_without_1x2({ {1, 5}, {10, 99} });
    BOOST_CHECK(A.copyWithout(1, 2) == submatrix_without_1x2);
    Matrix<float, 2, 2> submatrix_without_2x0({ {5, 9}, {2, -1} });
    BOOST_CHECK(A.copyWithout(2, 0) == submatrix_without_2x0);
    Matrix<float, 2, 2> submatrix_without_2x1({ {1, 9}, {-3, -1} });
    BOOST_CHECK(A.copyWithout(2, 1) == submatrix_without_2x1);
    Matrix<float, 2, 2> submatrix_without_2x2({ {1, 5}, {-3, 2} });
    BOOST_CHECK(A.copyWithout(2, 2) == submatrix_without_2x2);
}

BOOST_AUTO_TEST_CASE(test_submatrices_of_4x4) {
    Matrix<float, 4, 4> A({ {1, 5, 9, 4}, {1, -3, 2, -1}, {10, 99, 17, 2}, {1, 2, 3, 4} });
    Matrix<float, 3, 3> submatrix_without_0x0({ {-3, 2, -1}, {99, 17, 2}, {2, 3, 4} });
    BOOST_CHECK(A.copyWithout(0, 0) == submatrix_without_0x0);
    Matrix<float, 3, 3> submatrix_without_0x1({ {1, 2, -1}, {10, 17, 2}, {1, 3, 4} });
    BOOST_CHECK(A.copyWithout(0, 1) == submatrix_without_0x1);
    Matrix<float, 3, 3> submatrix_without_0x2({ {1, -3, -1}, {10, 99, 2}, {1, 2, 4} });
    BOOST_CHECK(A.copyWithout(0, 2) == submatrix_without_0x2);
    Matrix<float, 3, 3> submatrix_without_0x3({ {1, -3, 2}, {10, 99, 17}, {1, 2, 3} });
    BOOST_CHECK(A.copyWithout(0, 3) == submatrix_without_0x3);
    Matrix<float, 3, 3> submatrix_without_1x0({ {5, 9, 4}, {99, 17, 2}, {2, 3, 4} });
    BOOST_CHECK(A.copyWithout(1, 0) == submatrix_without_1x0);
    Matrix<float, 3, 3> submatrix_without_1x1({ {1, 9, 4}, {10, 17, 2}, {1, 3, 4} });
    BOOST_CHECK(A.copyWithout(1, 1) == submatrix_without_1x1);
    Matrix<float, 3, 3> submatrix_without_1x2({ {1, 5, 4}, {10, 99, 2}, {1, 2, 4} });
    BOOST_CHECK(A.copyWithout(1, 2) == submatrix_without_1x2);
    Matrix<float, 3, 3> submatrix_without_1x3({ {1, 5, 9}, {10, 99, 17}, {1, 2, 3} });
    BOOST_CHECK(A.copyWithout(1, 3) == submatrix_without_1x3);
    Matrix<float, 3, 3> submatrix_without_2x0({ {5, 9, 4}, {-3, 2, -1}, {2, 3, 4} });
    BOOST_CHECK(A.copyWithout(2, 0) == submatrix_without_2x0);
    Matrix<float, 3, 3> submatrix_without_2x1({ {1, 9, 4}, {1, 2, -1}, {1, 3, 4} });
    BOOST_CHECK(A.copyWithout(2, 1) == submatrix_without_2x1);
    Matrix<float, 3, 3> submatrix_without_2x2({ {1, 5, 4}, {1, -3, -1}, {1, 2, 4} });
    BOOST_CHECK(A.copyWithout(2, 2) == submatrix_without_2x2);
    Matrix<float, 3, 3> submatrix_without_2x3({ {1, 5, 9}, {1, -3, 2}, {1, 2, 3} });
    BOOST_CHECK(A.copyWithout(2, 3) == submatrix_without_2x3);
    Matrix<float, 3, 3> submatrix_without_3x0({ {5, 9, 4}, {-3, 2, -1}, {99, 17, 2} });
    BOOST_CHECK(A.copyWithout(3, 0) == submatrix_without_3x0);
    Matrix<float, 3, 3> submatrix_without_3x1({ {1, 9, 4}, {1, 2, -1}, {10, 17, 2} });
    BOOST_CHECK(A.copyWithout(3, 1) == submatrix_without_3x1);
    Matrix<float, 3, 3> submatrix_without_3x2({ {1, 5, 4}, {1, -3, -1}, {10, 99, 2} });
    BOOST_CHECK(A.copyWithout(3, 2) == submatrix_without_3x2);
    Matrix<float, 3, 3> submatrix_without_3x3({ {1, 5, 9}, {1, -3, 2}, {10, 99, 17} });
    BOOST_CHECK(A.copyWithout(3, 3) == submatrix_without_3x3);
}

BOOST_AUTO_TEST_CASE(test_LU_factorization_2x2) {
    Matrix<float, 2, 2> A({ {1, 2}, {3, 4} });
    if (auto factors = LUP::decompose(A)) {
        BOOST_CHECK(floats::equal(factors->LU(0,0), 3.0f));
        BOOST_CHECK(floats::equal(factors->LU(0,1), 4.0f));
        BOOST_CHECK(floats::equal(factors->LU(1,0), 0.333333f));
        BOOST_CHECK(floats::equal(factors->LU(1,1), 0.666667f));
    }
    else {
        BOOST_CHECK_MESSAGE(false, "Failed LUP decomposition.");
    }
}


/*
BOOST_AUTO_TEST_CASE(test_LU_factorization_3x3) {
  Matrix<3, 3> A({{1, 2, 0}, {3, -2, 4}, {0, -1, 7}});
  auto A_factors = LU_factorize(A);
  Matrix<3, 3> expected_lower({{1, 0, 0}, {3, 1, 0}, {0, 0.125, 1}});
  Matrix<3, 3> expected_upper({{1, 2, 0}, {0, -8, 4}, {0, 0, 6.5}});
  BOOST_CHECK(A_factors.lower == expected_lower);
  BOOST_CHECK(A_factors.upper == expected_upper);
}

BOOST_AUTO_TEST_CASE(test_LU_factorization_4x4) {
  Matrix<4, 4> A({{1, 0, 0, 1}, {3, 0, 0, 0}, {0, 0, -1, 7}, {4, 9, 10, -5}});
  auto A_factors = LU_factorize(A);
  Matrix<4, 4> expected_lower(
      {{1, 0, 0, 0}, {3, 1, 0, 0}, {0, 0, 1, 0}, {4, 0, 0, 1}});
  Matrix<4, 4> expected_upper(
      {{1, 0, 0, 1}, {0, 9, 10, -9}, {0, 0, -1, 7}, {0, 0, 0, -3}});
  std::cout << A << std::endl;
  std::cout << A_factors.lower << std::endl;
  std::cout << A_factors.upper << std::endl;
  std::cout << A_factors.lower * A_factors.upper << std::endl;
  BOOST_CHECK(A_factors.lower == expected_lower);
  BOOST_CHECK(A_factors.upper == expected_upper);
}
*/

BOOST_AUTO_TEST_CASE(test_determinants) {
    Matrix<float, 2, 2> A({ {1, 2}, {3, 4} });
    BOOST_CHECK(floats::equal(det(A), -2));
    Matrix<float, 3, 3> B({ {1, 2, 6}, {-5, 8, -4}, {2, 6, 4} });
    BOOST_CHECK(floats::equal(det(B), -196));
    Matrix<float, 4, 4> C({ {-2, -8, 3, 5}, {-3, 1, 7, 3}, {1, 2, -9, 6}, {-6, 7, 7, -9} });
    BOOST_CHECK(floats::equal(det(C), -4071));
    Matrix<float, 4, 4> D({ {1, 0, 0, 1}, {3, 0, 0, 0}, {0, 0, -1, 7}, {4, 9, 10, -5} });
    BOOST_CHECK(floats::equal(det(D), -27));
    Matrix<float, 2, 2> Zero({ {0, 0}, {0, 0} });
    BOOST_CHECK(det(Zero) == 0);
}

BOOST_AUTO_TEST_CASE(test_invert_matrix) {
  Matrix<float, 4, 4> A({{-5, 2, 6, -8}, {1, -5, 1, 8}, {7, 7, -6, -7}, {1, -3, 7, 4}});
  Matrix<float, 4, 4> expected({{0.21805, 0.45113, 0.24060, -0.04511},
                         {-0.80827, -1.45677, -0.44361, 0.52068},
                         {-0.07895, -0.22368, -0.05263, 0.19737},
                         {-0.52256, -0.81391, -0.30075, 0.30639}});
  invert(A);
  BOOST_CHECK(A == expected);
}

BOOST_AUTO_TEST_CASE(test_multiplications_of_four_3x3_matrices) {
    Matrix<float, 3, 3> A({ {1, 5, 9}, {-3, 2, -1}, {10, 99, 2} });
    Matrix<float, 3, 3> B({ {-1, 2.5f, 9.2f}, {0, 6, -4.4f}, {3.3f, 14.2f, 2.3f} });
    Matrix<float, 3, 3> AxB({ {28.7f, 160.3f, 7.9f}, {-0.3f, -9.7f, -38.7f}, {-3.4f, 647.4f, -339} });
    BOOST_CHECK(A * B == AxB);
    Matrix<float, 3, 3> C({ {1, 1, 3}, {-3.1, 1.1, -0.3}, {0.6, 9.9, 2.2} });
    Matrix<float, 3, 3> AxBxC({ {-463.49f, 283.24f, 55.39f}, {6.55f, -394.1f, -83.13f}, {-2213.74f, -2647.36f, -950.22f} });
    BOOST_CHECK(AxB*C == AxBxC);
    Matrix<float, 3, 3> D({ {3, 4, 5}, {-1, -1.1, -2.3}, {6.6, 2.9, 3.2} });
    Matrix<float, 3, 3> expected({ { -1308.136f, -2004.893f, -2791.654f }, { -134.908f, 218.633f, 673.164f }, { -10265.312f, -8698.502f, -8020.476f } });
    BOOST_CHECK(AxBxC * D == expected);
}
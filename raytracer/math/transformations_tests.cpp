#define BOOST_TEST_DYN_LINK
#ifdef STAND_ALONE
#   define BOOST_TEST_MODULE Main
#endif
#include <boost/test/unit_test.hpp>
#include "matrix.h"
#include "transformation.h"
#include "lup_decomposition.h"
#include "constants.h"

BOOST_AUTO_TEST_CASE(test_translation_of_point) {
    Matrix<int, 4, 1> point({ {1}, {2}, {3}, {1} });
    auto translationMatrix = Transformation::translation3D(1, 0, 0);
    Matrix<int, 4, 1> expected({ {2}, {2}, {3}, {1} });
    BOOST_CHECK(translationMatrix * point == expected);

    Matrix<float, 4, 1> pointFloat({ {1.31f}, {2.21f}, {3.33f}, {1} });
    auto translationMatrixFloat = Transformation::translation3D(1.21f, 1.3f, 2.23f);
    Matrix<float, 4, 1> expectedFloat({ {2.52f}, {3.51f}, {5.56f}, {1} });
    BOOST_CHECK(translationMatrixFloat * pointFloat == expectedFloat);
}

BOOST_AUTO_TEST_CASE(test_translation_not_affecting_vectors) {
    Matrix<int, 4, 1> vec({ {1}, {2}, {3}, {0} });
    auto translationMatrix = Transformation::translation3D(1, 0, 0);
    BOOST_CHECK(translationMatrix * vec == vec);

    Matrix<int, 4, 1> anotherVec({ {1}, {2}, {3}, {0} });
    auto anotherTranslationMatrix = Transformation::translation3D(1, 2, 3);
    BOOST_CHECK(anotherTranslationMatrix * anotherVec == anotherVec);

    Matrix<float, 4, 1> vecFloat({ {1.31f}, {2.21f}, {3.33f}, {0} });
    auto translationMatrixFloat = Transformation::translation3D(1.21f, 1.3f, 2.23f);
    BOOST_CHECK(translationMatrixFloat * vecFloat == vecFloat);
}


BOOST_AUTO_TEST_CASE(test_scaling_a_point) {
    Matrix<int, 4, 1> point({ {-4}, {6}, {8}, {1} });
    auto scaleMatrix = Transformation::scale3D(2, 3, 4);
    Matrix<int, 4, 1> expected({ {-8}, {18}, {32}, {1} });
    BOOST_CHECK(scaleMatrix * point == expected);

    Matrix<float, 4, 1> pointFloat({ {1.31f}, {2.21f}, {3.33f}, {1} });
    auto scaleMatrixFloat = Transformation::scale3D(1.21f, 1.3f, 2.23f);
    Matrix<float, 4, 1> expectedFloat({ {1.5851f}, {2.873f}, {7.4259f}, {1} });
    BOOST_CHECK(scaleMatrixFloat * pointFloat == expectedFloat);
}

BOOST_AUTO_TEST_CASE(test_scaling_a_vector) {
    Matrix<int, 4, 1> vec({ {-4}, {6}, {8}, {0} });
    auto scaleMatrix = Transformation::scale3D(2, 3, 4);
    Matrix<int, 4, 1> expected({ {-8}, {18}, {32}, {0} });
    BOOST_CHECK(scaleMatrix * vec == expected);

    Matrix<float, 4, 1> vecFloat({ {1.31f}, {2.21f}, {3.33f}, {0} });
    auto scaleMatrixFloat = Transformation::scale3D(1.21f, 1.3f, 2.23f);
    Matrix<float, 4, 1> expectedFloat({ {1.5851f}, {2.873f}, {7.4259f}, {0} });
    BOOST_CHECK(scaleMatrixFloat * vecFloat == expectedFloat);
}

BOOST_AUTO_TEST_CASE(test_scaling_a_vector_by_the_inverse_of_a_scaling_matrix) {
    Matrix<float, 4, 1> vec({ {-4}, {6}, {8}, {0} });
    auto scaleMatrix = Transformation::scale3D(2.0, 3.0, 4.0);
    invert(scaleMatrix);
    Matrix<double, 4, 1> expected({ {-2}, {2}, {2}, {0} });
    BOOST_CHECK(scaleMatrix * vec == expected);
}

BOOST_AUTO_TEST_CASE(test_rot_point_around_x_axis) {
    Matrix<int, 4, 1> point({ {0}, {1}, {0}, {1} });
    auto halfQuarterRotX = Transformation::rotX(Constants::PI/4);
    Matrix<double, 4, 1> pointRotatedHalfQuarter({ {0}, {std::sqrt(2)/2}, {std::sqrt(2) / 2}, {1}});
    BOOST_CHECK(halfQuarterRotX * point == pointRotatedHalfQuarter);

    invert(halfQuarterRotX);
    Matrix<double, 4, 1> pointRotatedHalfQuarterCounterClockwise({ {0}, {std::sqrt(2) / 2}, {-std::sqrt(2) / 2}, {1} });
    BOOST_CHECK(halfQuarterRotX * point == pointRotatedHalfQuarterCounterClockwise);

    auto fullQuarterRotX = Transformation::rotX(Constants::PI / 2);
    Matrix<double, 4, 1> pointRotatedFullQuarter({ {0}, {0}, {1}, {1} });
    BOOST_CHECK(fullQuarterRotX * point == pointRotatedFullQuarter);
}
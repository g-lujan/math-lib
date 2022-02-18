#define BOOST_TEST_DYN_LINK
#ifdef STAND_ALONE
#   define BOOST_TEST_MODULE Main
#endif
#include <boost/test/unit_test.hpp>
#include "matrix.h"
#include "transformation.h"
#include "lup_decomposition.h"

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
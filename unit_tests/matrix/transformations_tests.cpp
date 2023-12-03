#ifdef STAND_ALONE
#   define BOOST_TEST_MODULE Main
#endif
#include <boost/test/unit_test.hpp>
#include "math_lib/matrix/matrix.h"

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
    Matrix<float, 4, 1> pointRotatedHalfQuarter({ {0}, {std::sqrtf(2)/2}, {std::sqrtf(2) / 2}, {1}});
    BOOST_CHECK(halfQuarterRotX * point == pointRotatedHalfQuarter);

    invert(halfQuarterRotX);
    Matrix<float, 4, 1> pointRotatedHalfQuarterCounterClockwise({ {0}, {std::sqrtf(2) / 2}, {-std::sqrtf(2) / 2}, {1} });
    BOOST_CHECK(halfQuarterRotX * point == pointRotatedHalfQuarterCounterClockwise);

    auto fullQuarterRotX = Transformation::rotX(Constants::PI / 2);
    Matrix<float, 4, 1> pointRotatedFullQuarter({ {0}, {0}, {1}, {1} });
    BOOST_CHECK(fullQuarterRotX * point == pointRotatedFullQuarter);
}

BOOST_AUTO_TEST_CASE(test_rot_point_around_y_axis) {
    Matrix<int, 4, 1> point({ {0}, {0}, {1}, {1} });
    auto halfQuarterRotY = Transformation::rotY(Constants::PI / 4);
    Matrix<float, 4, 1> pointRotatedHalfQuarter({ {std::sqrtf(2) / 2}, {0}, {std::sqrtf(2) / 2}, {1} });
    BOOST_CHECK(halfQuarterRotY * point == pointRotatedHalfQuarter);

    invert(halfQuarterRotY);
    Matrix<float, 4, 1> pointRotatedHalfQuarterCounterClockwise({ {-std::sqrtf(2) / 2}, {0}, {std::sqrtf(2) / 2}, {1} });
    BOOST_CHECK(halfQuarterRotY * point == pointRotatedHalfQuarterCounterClockwise);

    auto fullQuarterRotY = Transformation::rotY(Constants::PI / 2);
    Matrix<float, 4, 1> pointRotatedFullQuarter({ {1}, {0}, {0}, {1} });
    BOOST_CHECK(fullQuarterRotY * point == pointRotatedFullQuarter);
}

BOOST_AUTO_TEST_CASE(test_rot_point_around_z_axis) {
    Matrix<int, 4, 1> point({ {0}, {1}, {0}, {1} });
    auto halfQuarterRotZ = Transformation::rotZ(Constants::PI / 4);
    Matrix<float, 4, 1> pointRotatedHalfQuarter({ {-std::sqrtf(2) / 2}, {std::sqrtf(2) / 2}, {0}, {1} });
    BOOST_CHECK(halfQuarterRotZ * point == pointRotatedHalfQuarter);

    invert(halfQuarterRotZ);
    Matrix<float, 4, 1> pointRotatedHalfQuarterCounterClockwise({ {std::sqrtf(2) / 2}, {std::sqrtf(2) / 2}, {0}, {1} });
    BOOST_CHECK(halfQuarterRotZ * point == pointRotatedHalfQuarterCounterClockwise);

    auto fullQuarterRotZ = Transformation::rotZ(Constants::PI / 2);
    Matrix<float, 4, 1> pointRotatedFullQuarter({ {-1}, {0}, {0}, {1} });
    BOOST_CHECK(fullQuarterRotZ * point == pointRotatedFullQuarter);
}

BOOST_AUTO_TEST_CASE(test_shearing_x_in_proportion_to_y) {
    Matrix<int, 4, 1> point({ {2}, {3}, {4}, {1} });
    auto shearing = Transformation::shearing(1, 0, 0, 0, 0, 0);
    Matrix<int, 4, 1> expected({ {5}, {3}, {4}, {1} });
    BOOST_CHECK(shearing * point == expected);

    Matrix<float, 4, 1> pointf({ {2.2f}, {3.1f}, {4.9f}, {1.0f} });
    Matrix<float, 4, 1> expectedf({ {5.3f}, {3.1f}, {4.9f}, {1.0f} });
    BOOST_CHECK(shearing * pointf == expectedf);
}

BOOST_AUTO_TEST_CASE(test_shearing_x_in_proportion_to_z) {
    Matrix<int, 4, 1> point({ {2}, {3}, {4}, {1} });
    auto shearing = Transformation::shearing(0, 2, 0, 0, 0, 0);
    Matrix<int, 4, 1> expected({ {10}, {3}, {4}, {1} });
    BOOST_CHECK(shearing * point == expected);

    Matrix<float, 4, 1> pointf({ {2.2f}, {3.1f}, {4.9f}, {1.0f} });
    Matrix<float, 4, 1> expectedf({ {12.0f}, {3.1f}, {4.9f}, {1.0f} });
    BOOST_CHECK(shearing * pointf == expectedf);
}

BOOST_AUTO_TEST_CASE(test_shearing_y_in_proportion_to_x) {
    Matrix<int, 4, 1> point({ {2}, {3}, {4}, {1} });
    auto shearing = Transformation::shearing(0, 0, 1, 0, 0, 0);
    Matrix<int, 4, 1> expected({ {2}, {5}, {4}, {1} });
    BOOST_CHECK(shearing * point == expected);

    Matrix<float, 4, 1> pointf({ {2.2f}, {3.1f}, {4.9f}, {1.0f} });
    Matrix<float, 4, 1> expectedf({ {2.2f}, {5.3f}, {4.9f}, {1.0f} });
    BOOST_CHECK(shearing * pointf == expectedf);
}

BOOST_AUTO_TEST_CASE(test_shearing_y_in_proportion_to_z) {
    Matrix<int, 4, 1> point({ {2}, {3}, {4}, {1} });
    auto shearing = Transformation::shearing(0, 0, 0, 1, 0, 0);
    Matrix<int, 4, 1> expected({ {2}, {7}, {4}, {1} });
    BOOST_CHECK(shearing * point == expected);

    Matrix<float, 4, 1> pointf({ {2.2f}, {3.1f}, {4.9f}, {1.0f} });
    Matrix<float, 4, 1> expectedf({ {2.2f}, {8.0f}, {4.9f}, {1.0f} });
    BOOST_CHECK(shearing * pointf == expectedf);
}

BOOST_AUTO_TEST_CASE(test_shearing_z_in_proportion_to_x) {
    Matrix<int, 4, 1> point({ {2}, {3}, {4}, {1} });
    auto shearing = Transformation::shearing(0, 0, 0, 0, 3, 0);
    Matrix<int, 4, 1> expected({ {2}, {3}, {10}, {1} });
    BOOST_CHECK(shearing * point == expected);

    Matrix<float, 4, 1> pointf({ {2.2f}, {3.1f}, {4.9f}, {1.0f} });
    Matrix<float, 4, 1> expectedf({ {2.2f}, {3.1f}, {11.5f}, {1.0f} });
    BOOST_CHECK(shearing * pointf == expectedf);
}

BOOST_AUTO_TEST_CASE(test_shearing_z_in_proportion_to_y) {
    Matrix<int, 4, 1> point({ {2}, {3}, {4}, {1} });
    auto shearing = Transformation::shearing(0, 0, 0, 0, 0, 1);
    Matrix<int, 4, 1> expected({ {2}, {3}, {7}, {1} });
    BOOST_CHECK(shearing * point == expected);

    Matrix<float, 4, 1> pointf({ {2.2f}, {3.1f}, {4.9f}, {1.0f} });
    Matrix<float, 4, 1> expectedf({ {2.2f}, {3.1f}, {8.0f}, {1.0f} });
    BOOST_CHECK(shearing * pointf == expectedf);
}

BOOST_AUTO_TEST_CASE(test_compound_shearing) {
    Matrix<int, 4, 1> point({ {2}, {3}, {4}, {1} });
    auto shearing = Transformation::shearing(2.1f, 2.0f, 1.3f, 0.1f, 0.0f, 1.0f);
    Matrix<float, 4, 1> expected({ {2+2.1f*3+2.0f*4}, {3+1.3f*2+0.1f*4}, {4+1.0f*3}, {1} });
    BOOST_CHECK(shearing * point == expected);
}

BOOST_AUTO_TEST_CASE(test_trasformations_in_sequence) {
    Matrix<int, 4, 1> point({ {1}, {0}, {1}, {1} });
    auto rotX = Transformation::rotX(Constants::PI/2);
    auto scale = Transformation::scale3D(5, 5, 5);
    auto translation = Transformation::translation3D(10, 5, 7);
    // apply rot
    auto pointRotated = rotX * point;
    // apply scale
    auto pointRotatedAndScaled = scale * pointRotated;
    // apply translation
    auto pointRotatedAndScaledTranslated = translation * pointRotatedAndScaled;

    Matrix<float, 4, 1> expected({ {15}, {0}, {7}, {1} });
    BOOST_CHECK(pointRotatedAndScaledTranslated == expected);
    BOOST_CHECK(pointRotatedAndScaledTranslated == translation * scale * rotX * point);
}
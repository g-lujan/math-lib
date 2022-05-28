#ifdef STAND_ALONE
#define BOOST_TEST_MODULE Main
#endif
#include <boost/test/unit_test.hpp>
#include <raytracer/math.h>
#include <raytracer/graphics.h>

BOOST_AUTO_TEST_CASE(test_sphere_default_transformation) {
    Sphere s;
    BOOST_CHECK(s.transformation() == Transformation::IDENTITY_F_4X4);
}

BOOST_AUTO_TEST_CASE(test_sphere_change_transformation) {
    Sphere s;
    auto newTransformation = Transformation::translation3D(1.0f, 2.0f, 3.0f);
    s.transformation(newTransformation);
    BOOST_CHECK(s.transformation() != Transformation::IDENTITY_F_4X4);
    BOOST_CHECK(s.transformation() == newTransformation);
}

BOOST_AUTO_TEST_CASE(test_intersecting_a_scaled_sphere_with_a_ray) {
    Ray3D r({ {0},{0},{ -5} }, { {0},{0},{1} });
    Sphere s;
    s.transformation(Transformation::scale3D(2.0f, 2.0f, 2.0f));
    Intersections intersections = Geometry::intersections(r, s);
    BOOST_CHECK(intersections.size() == 2);
    BOOST_CHECK(floats::equal(intersections[0], 3.0f) && floats::equal(intersections[1], 7.0f));
}

BOOST_AUTO_TEST_CASE(test_intersecting_a_translated_sphere_with_a_ray) {
    Ray3D r({ {0},{0},{ -5} }, { {0},{0},{1} });
    Sphere s;
    s.transformation(Transformation::translation3D(5.0f, 0.0f, 0.0f));
    Intersections intersections = Geometry::intersections(r, s);
    BOOST_CHECK(intersections.empty());
}
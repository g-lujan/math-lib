#ifdef STAND_ALONE
#define BOOST_TEST_MODULE Main
#endif
#include <boost/test/unit_test.hpp>
#include <raytracer/math.h>
#include "raytracer/graphics.h"

using Geometry::point3D;
using Geometry::vec3D;

BOOST_AUTO_TEST_CASE(test_create_point3D) {
	auto point = point3D(1.0f, 2.0f, 3.0f);
    BOOST_CHECK(point(0, 0) == 1.0f);
    BOOST_CHECK(point(1, 0) == 2.0f);
    BOOST_CHECK(point(2, 0) == 3.0f);
    BOOST_CHECK(point(3, 0) == 1.0f);
}

BOOST_AUTO_TEST_CASE(test_create_vec3D) {
    auto vec = vec3D(1.0f, 2.0f, 3.0f);
    BOOST_CHECK(vec(0, 0) == 1.0f);
    BOOST_CHECK(vec(1, 0) == 2.0f);
    BOOST_CHECK(vec(2, 0) == 3.0f);
    BOOST_CHECK(vec(3, 0) == 0.0f);
}

BOOST_AUTO_TEST_CASE(test_create_ray3D) {
    Ray3D ray({ { 1.0f}, {2.0f}, {3.0f} }, { { 1.0f}, {2.0f}, {3.0f} });
    BOOST_CHECK(ray.origin() == point3D(1.0f, 2.0f, 3.0f));
    BOOST_CHECK(ray.direction() == vec3D(1.0f, 2.0f, 3.0f));
}

BOOST_AUTO_TEST_CASE(test_ray_propagation) {
    Ray3D ray({ { 1.0f}, {2.0f}, {3.0f} }, { { 1.0f}, {2.0f}, {3.0f} });
    BOOST_CHECK(ray.propagate(2) == point3D(3.0f, 6.0f, 9.0f));
    BOOST_CHECK(ray.propagate(0.5f) == point3D(1.5f, 3.0f, 4.5f));
    BOOST_CHECK(ray.propagate(-1.5f) == point3D(-0.5f, -1.0f, -1.5f));
}
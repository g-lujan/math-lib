#ifdef STAND_ALONE
#define BOOST_TEST_MODULE Main
#endif
#include <boost/test/unit_test.hpp>
#include <raytracer/math.h>
#include <raytracer/graphics.h>

BOOST_AUTO_TEST_CASE(test_intersection_in_two_points_of_a_sphere) {
	Ray3D r({ {0},{0},{ -5} }, { {0},{0},{1} });
	Sphere s;
	Intersections intersections = Geometry::intersections(r, s);
	BOOST_CHECK(intersections.size() == 2);
	BOOST_CHECK(floats::equal(intersections[0], 4.0f));
	BOOST_CHECK(floats::equal(intersections[1], 6.0f));
}

BOOST_AUTO_TEST_CASE(test_intersection_at_a_tangent_of_a_sphere) {
	Ray3D r({ {0},{1},{ -5} }, { {0},{0},{1} });
	Sphere s;
	Intersections intersections = Geometry::intersections(r, s);
	BOOST_CHECK(intersections.size() == 1);
	BOOST_CHECK(floats::equal(intersections[0], 5.0f));
}

BOOST_AUTO_TEST_CASE(test_no_intersection) {
	Ray3D r({ {0},{2},{ -5} }, { {0},{0},{1} });
	Sphere s;
	Intersections intersections = Geometry::intersections(r, s);
	BOOST_CHECK(intersections.empty());
}

BOOST_AUTO_TEST_CASE(test_intersection_with_ray_originated_inside_sphere) {
	Ray3D r({ {0},{0},{0} }, { {0},{0},{1} });
	Sphere s;
	Intersections intersections = Geometry::intersections(r, s);
	BOOST_CHECK(intersections.size() == 2);
	BOOST_CHECK(floats::equal(intersections[0], -1.0f));
	BOOST_CHECK(floats::equal(intersections[1], 1.0f));
}

BOOST_AUTO_TEST_CASE(test_intersection_with_sphere_behind_ray_origin) {
	Ray3D r({ {0},{0},{5} }, { {0},{0},{1} });
	Sphere s;
	Intersections intersections = Geometry::intersections(r, s);
	BOOST_CHECK(intersections.size() == 2);
	BOOST_CHECK(floats::equal(intersections[0], -6.0f));
	BOOST_CHECK(floats::equal(intersections[1], -4.0f));
}
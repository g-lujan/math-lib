#define BOOST_TEST_DYN_LINK
#ifdef STAND_ALONE
#define BOOST_TEST_MODULE Main
#endif
#include <boost/test/unit_test.hpp>
#include "../canvas.h"
#include "../../math/float_operations.h"
#include "../render.h"
#include <iostream>

BOOST_AUTO_TEST_CASE(test_canvas_setup) {
    Canvas c(800, 600);
    for (int i = 0; i < c.height(); i++) {
        for (int j = 0; j < c.width(); j++) {
            auto position = Matrix<int, 4, 1>({ {i}, {j}, {0}, {1} });
            BOOST_CHECK(floats::equal(c.colorAt(position).r(), 0.0f));
            BOOST_CHECK(floats::equal(c.colorAt(position).g(), 0.0f));
            BOOST_CHECK(floats::equal(c.colorAt(position).b(), 0.0f));
            BOOST_CHECK(floats::equal(c.colorAt(position).alpha(), 0.0f));
        }
    }
}
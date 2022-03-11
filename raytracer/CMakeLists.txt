cmake_minimum_required (VERSION 3.8)

find_package(Boost COMPONENTS unit_test_framework REQUIRED)
include_directories(${Boost_INCLUDE_DIR})
add_executable (raytracer 
 "math/matrix.tcc" 
 "math/float_operations.cpp" 
 "math/lup_decomposition.tcc" 
 "math/transformation.tcc"
 "math/constants.h" 
 "graphics/canvas.h"
 "graphics/render.cpp"
 "graphics/image.h"
 "test_main.cpp" "math/matrix_tests.cpp" "math/transformations_tests.cpp"  "graphics/tests/canvas_tests.cpp"  )
 ADD_EXECUTABLE(circle 
 "math/matrix.tcc" 
 "math/float_operations.cpp" 
 "math/lup_decomposition.tcc" 
 "math/transformation.tcc"
 "math/constants.h" 
 "graphics/canvas.h"
 "graphics/render.cpp"
 "graphics/image.h"
 "examples/circle/circle.cpp"  )

set_target_properties(raytracer PROPERTIES CXX_STANDARD 17)
set_target_properties(circle PROPERTIES CXX_STANDARD 17)
target_link_libraries(raytracer PRIVATE ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})
target_link_libraries(circle PRIVATE ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})
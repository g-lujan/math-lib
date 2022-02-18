cmake_minimum_required (VERSION 3.8)

find_package(Boost COMPONENTS unit_test_framework REQUIRED)
include_directories(${Boost_INCLUDE_DIR})
add_executable (raytracer 
 "math/matrix.tcc" 
 "math/float_operations.cpp" 
 "math/lup_decomposition.tcc" 
 "math/transformation.tcc"
 "math/matrix_tests.cpp" "math/transformations_tests.cpp" "math/test_main.cpp")
set_target_properties(raytracer PROPERTIES CXX_STANDARD 17)
target_link_libraries(raytracer PRIVATE ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})

find_package(Boost COMPONENTS unit_test_framework REQUIRED)
include_directories(${Boost_INCLUDE_DIR})
add_definitions (-DBOOST_TEST_DYN_LINK)

add_executable (Test 
test_main.cpp 
math/matrix_tests.cpp 
math/transformations_tests.cpp
graphics/canvas_tests.cpp 
graphics/geometry_tests.cpp
graphics/ray_tests.cpp)

target_link_libraries (Test
 raytracer
 ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
 )

# testing command
# declares a test with our executable
add_test(NAME test1 COMMAND Test)
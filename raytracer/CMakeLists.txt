cmake_minimum_required (VERSION 3.8)

find_package(Boost COMPONENTS unit_test_framework REQUIRED)
include_directories(${Boost_INCLUDE_DIR})
add_executable (raytracer "test.cpp")
target_link_libraries(raytracer PRIVATE ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})

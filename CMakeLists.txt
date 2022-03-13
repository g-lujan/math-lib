cmake_minimum_required (VERSION 3.8)
set (CMAKE_CXX_STANDARD 17)

project(raytracer VERSION 0.0.1 DESCRIPTION "a raytracer implemented from scratch")

add_subdirectory ("raytracer")
add_subdirectory ("unit_tests")
add_subdirectory ("examples")
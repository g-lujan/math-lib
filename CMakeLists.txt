cmake_minimum_required(VERSION 3.11)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_TOOLCHAIN_FILE "C:/vcpkg/scripts/buildsystems/vcpkg.cmake")

project(raytracer VERSION 0.0.1 DESCRIPTION "a math lib implemented from scratch")

add_subdirectory ("math_lib")
add_subdirectory ("unit_tests")
add_subdirectory ("perf_tests")
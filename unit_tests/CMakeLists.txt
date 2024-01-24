find_package(Boost REQUIRED COMPONENTS unit_test_framework)
include_directories(${Boost_INCLUDE_DIR})
add_definitions(-DBOOST_TEST_DYN_LINK)

add_executable (Test 
test_main.cpp 
matrix/matrix_tests.cpp 
matrix/transformations_tests.cpp)

target_link_libraries (Test math_lib Boost::unit_test_framework)

# testing command
# declares a test with our executable
add_test(NAME test1 COMMAND Test)
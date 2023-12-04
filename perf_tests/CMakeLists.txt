add_executable (PerfTest product_test.cpp)
file(COPY generate_input.py DESTINATION "${CMAKE_CURRENT_BINARY_DIR}/Test")
file(COPY product_test_numpy.py DESTINATION "${CMAKE_CURRENT_BINARY_DIR}/Test")

# run with 'cmake --build build-msvc --target generate_test_matrices_target'
# this is not working...
add_custom_target(generate_test_matrices_target 
	COMMAND python ${CMAKE_CURRENT_SOURCE_DIR}/perf_tests/generate_input.py
	COMMENT "Generating test inputs for performance tests" VERBATIM
	WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
)

set_target_properties(PerfTest PROPERTIES RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_CURRENT_BINARY_DIR}/Test)

target_link_libraries (PerfTest math_lib)

# testing command
# declares a test with our executable
add_test(NAME perf_test COMMAND PerfTest)

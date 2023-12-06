find_package(Python3 REQUIRED)

file(COPY generate_input.py DESTINATION "${CMAKE_CURRENT_BINARY_DIR}/Test")
file(COPY product_test_numpy.py DESTINATION "${CMAKE_CURRENT_BINARY_DIR}/Test")

add_executable (PerfTest product_test.cpp)

add_custom_target(
        build_perf_test_matrices
        DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/A.txt ${CMAKE_CURRENT_BINARY_DIR}/B.txt
)

# not working with Visual Studio generator (doesn't even run)
add_custom_command(
    OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/A.txt ${CMAKE_CURRENT_BINARY_DIR}/B.txt
	COMMAND Python3::Interpreter ${CMAKE_CURRENT_SOURCE_DIR}/generate_input.py
	COMMENT "Generating test inputs for performance tests" VERBATIM
)


add_dependencies(PerfTest build_perf_test_matrices)
target_link_libraries (PerfTest math_lib)

add_library(math_lib)
set_target_properties(math_lib PROPERTIES LINKER_LANGUAGE CXX)

add_subdirectory(src/matrix)
source_group(matrix REGULAR_EXPRESSION "${CMAKE_CURRENT_SOURCE_DIR}/src/matrix/*")

add_subdirectory(src/base_operations)
source_group(base_operations REGULAR_EXPRESSION "${CMAKE_CURRENT_SOURCE_DIR}/src/base_operations/*")

target_include_directories(math_lib PUBLIC  "${CMAKE_CURRENT_SOURCE_DIR}/include"
                                    PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/src")
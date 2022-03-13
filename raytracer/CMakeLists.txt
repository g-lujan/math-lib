add_library( raytracer STATIC
"${CMAKE_CURRENT_SOURCE_DIR}/src/math/float_operations.cpp" 
"${CMAKE_CURRENT_SOURCE_DIR}/src/graphics/render.cpp")

target_include_directories(raytracer PUBLIC  "${CMAKE_CURRENT_SOURCE_DIR}/include"
                                     PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/src")
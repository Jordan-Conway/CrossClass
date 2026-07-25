cmake_minimum_required(VERSION 3.28)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)

project(CrossClass)

add_subdirectory(src/ccx_reader)
add_subdirectory(src/cross_class_lib)
add_subdirectory(src/cross_class_cli)


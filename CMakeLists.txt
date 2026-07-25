cmake_minimum_required(VERSION 3.28)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)

project(CrossClass)

add_subdirectory(src/ccx_reader)

add_executable(${CMAKE_PROJECT_NAME}
    src/main.c
)

target_link_libraries(
    ${CMAKE_PROJECT_NAME}
    PRIVATE
    ccx_reader
)


cmake_minimum_required(VERSION 3.28)
project(crossclass C)

set(CMAKE_C_STANDARD 17)

set(PROJECT_INCLUDES
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}/src/Data
    ${CMAKE_SOURCE_DIR}/src/Data/Tokens
    ${CMAKE_SOURCE_DIR}/tests
    ${CMAKE_SOURCE_DIR}/tests/*/*
)

file(GLOB SHARED_SRC
    ${CMAKE_SOURCE_DIR}/src/Data/*.c
    ${CMAKE_SOURCE_DIR}/src/Data/Tokens/*.c
    ${CMAKE_SOURCE_DIR}/src/*.c
)

file(GLOB TESTS_SRC
    ${CMAKE_SOURCE_DIR}/tests/*/*.c
)

list(REMOVE_ITEM SHARED_SRC
    ${CMAKE_SOURCE_DIR}/src/main.c
)

# Main application
add_executable(crossclass
    src/main.c
    ${SHARED_SRC}
)

target_include_directories(crossclass PRIVATE ${PROJECT_INCLUDES})

# Test executable
add_executable(crossclass_tests
    tests/test.c
    ${SHARED_SRC}
    ${TESTS_SRC}
)

target_include_directories(crossclass_tests PRIVATE ${PROJECT_INCLUDES})
find_library(CUNIT_LIB cunit REQUIRED)
target_link_libraries(crossclass_tests PRIVATE ${CUNIT_LIB})

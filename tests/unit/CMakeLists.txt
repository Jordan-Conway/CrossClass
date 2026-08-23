cmake_minimum_required(VERSION 3.28)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin")
set(Source_Code_Directory "${CMAKE_CURRENT_SOURCE_DIR}/../../src")
set(Shared_Object_Directory "${CMAKE_CURRENT_SOURCE_DIR}/../../lib")

project(CrossClassTests)

#region Installed Packages
find_path(CUNIT_INCLUDE_DIR
    NAMES CUnit/CUnit.h
)

find_library(CUNIT_LIBRARY
    NAMES cunit
)

if(NOT CUNIT_INCLUDE_DIR OR NOT CUNIT_LIBRARY)
    message(FATAL_ERROR "CUnit not found")
endif()
#endregion

#region Add source libraries
add_library(ccx_reader SHARED IMPORTED)
set_target_properties(ccx_reader PROPERTIES
    IMPORTED_LOCATION "${Shared_Object_Directory}/ccx_reader.so"
    INTERFACE_INCLUDE_DIRECTORIES "${Source_Code_Directory}/ccx_reader/includes"
)

add_library(cross_class_lib SHARED IMPORTED)
set_target_properties(cross_class_lib PROPERTIES
    IMPORTED_LOCATION "${Shared_Object_Directory}/cross_class_lib.so"
    INTERFACE_INCLUDE_DIRECTORIES "${Source_Code_Directory}/cross_class_lib/includes"
)

#endregion

#region test project directories
add_subdirectory(./ccx_reader_tests)
add_subdirectory(./cross_class_lib_tests)
#endregion

#region create test executable
add_executable(cross_class_tests)

target_sources(cross_class_tests
    PUBLIC
    test.c)


target_link_libraries(cross_class_tests
    PRIVATE
    ccx_reader
    ccx_reader_tests
    cross_class_lib
    cross_class_lib_tests
    ${CUNIT_LIBRARY}
)

target_compile_options(cross_class_tests PRIVATE -Wall -Wextra -Werror -Wpedantic)
#endregion

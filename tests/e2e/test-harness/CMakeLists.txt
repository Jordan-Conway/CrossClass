add_library(test_harness SHARED)

target_sources(test_harness
    PRIVATE
    ./execute.hpp
    ./execute.cpp
    ./test_results.cpp
    ./transpiler_execution.cpp
    PUBLIC
    ./includes/test_results.hpp
    ./includes/transpiler_execution.hpp
)

target_include_directories(test_harness
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/includes
)

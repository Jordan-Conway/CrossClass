add_executable(transpiler_tests)

target_link_libraries(transpiler_tests
    PRIVATE
    test_harness
)

target_sources(transpiler_tests
    PRIVATE
    typescript_transpiler_tests.hpp
    typescript_transpiler_tests.cpp
    PUBLIC
    ./main.cpp
)

add_executable(test-harness)

target_sources(test-harness
    PRIVATE
    ./execute.hpp
    ./execute.cpp
    PUBLIC
    ./main.cpp
)

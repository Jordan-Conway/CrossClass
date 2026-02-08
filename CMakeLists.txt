cmake_minimum_required(VERSION 3.28.0)

project(crossclass C)

set(CMAKE_C_STANDARD 17)

include_directories(
    ./src
    ./src/Data
    ./src/Data/Tokens
)

file(GLOB SRC_FILES
    ./src/*.c
    ./src/Data/*.c
    ./src/Data/Tokens/*.c
)

add_executable(crossclass ${SRC_FILES})
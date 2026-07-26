#!/bin/bash
cmake -B ./build -DCMAKE_BUILD_TYPE=Debug

if [ $? -ne 0 ]; then
    echo "Failed to create project buildsystem"
    exit 1
fi

cmake --build ./build

if [ $? -ne 0 ]; then
    echo "Failed to build project"
    exit 1
fi

cd ./tests/unit
cmake -B ./build -DCMAKE_BUILD_TYPE=Debug

if [ $? -ne 0 ]; then
    echo "Failed to create test project buildsystem"
    exit 1
fi

cmake --build ./build

if [ $? -ne 0 ]; then
    echo "Failed to build test project"
    exit 1
fi

echo "Build succeeded"
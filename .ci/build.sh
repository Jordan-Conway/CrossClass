#!/bin/bash
cmake -B ./build

if [ $? -ne 0 ]; then
    echo "Failed to create project buildsystem"
    exit 1
fi

cmake --build ./build

if [ $? -ne 0 ]; then
    echo "Failed to build project"
    exit 1
fi

echo "Build succeeded"
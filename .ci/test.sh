#!/bin/bash
source .ci/build.sh
if [ $? -ne 0 ]; then
    echo "Failed to build source"
    exit 1
fi

cd ./tests/unit

cmake -B ./build
cmake --build ./build
if [ $? -ne 0 ]; then
    echo "Failed to build test executable"
    exit 1
fi

chmod +x ./bin/cross_class_tests

./bin/cross_class_tests
if [ $? -ne 0 ]; then
    echo "One or more tests failed"
    exit 1
fi

echo "Tests passed"

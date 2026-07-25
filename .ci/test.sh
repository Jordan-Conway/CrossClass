#!/bin/bash
source .ci/build.sh
if [ $? -ne 0 ]; then
    echo "Failed to build source"
    exit 1
fi

cmake -B ./tests/unit/build
cmake --build ./tests/unit/build
if [ $? -ne 0 ]; then
    echo "Failed to build test executable"
    exit 1
fi

./tests/unit/bin/cross_class_tests
if [ $? -ne 0 ]; then
    echo "One or more tests failed"
    exit 1
fi

echo "Tests passed"

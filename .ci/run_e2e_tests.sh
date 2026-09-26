#!/bin/bash

script_directory="$(dirname -- "$(readlink -f -- "$0")")"
cd "$script_directory/.."
echo "CWD for test script : ["$script_directory"]"

skip_build=1

while getopts "s" opt; do
    echo "Skipping build source step"
    skip_build=0;
done

if [ $skip_build -ne 0 ]; then
    ./.ci/build.sh

    if [ $? -ne 0 ]; then
        echo "Failed to build source"
        exit 1
    fi
fi

cd ./tests/e2e

cmake -B ./build
cmake --build ./build

if [ $? -ne 0 ]; then
    echo "Failed to build test executable(s)"
    exit 1
fi

chmod +x ./bin/transpiler_tests

cd ../..

./tests/e2e/bin/transpiler_tests
if [ $? -ne 0 ]; then
    echo "One or more tests failed"
    exit 1
fi

echo "Tests passed"
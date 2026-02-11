#!/bin/bash
./build/tests/bin/crossclass_tests

if [ $? -ne 0 ]; then
    echo "One or more tests failed"
    exit 1
fi

echo "Tests passed"

#!/bin/bash
executable_path="./bin/cross_class_cli"
test_executable_path="./tests/unit/bin/cross_class_tests"

mkdir -p reports

valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --log-file=./reports/cli_valgrind-out.txt ${executable_path} ./Examples/Person.ccd
valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --log-file=./reports/tests_valgrind-out.txt ${test_executable_path}
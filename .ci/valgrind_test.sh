#!/bin/bash
valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --log-file=./build/valgrind-out.txt ./build/crossclass/bin/crossclass ./Examples/Person.ccd

valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --log-file=./build/valgrind-tests-out.txt ./build/tests/bin/crossclass_tests 
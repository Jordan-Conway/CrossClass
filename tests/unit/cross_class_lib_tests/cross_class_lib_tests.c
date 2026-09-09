#include "./cross_class_lib_tests.h"

#include "./data_parser_tests/data_parser_tests.h"
#include "./version_tests/version_tests.h"
#include "data_parser_tests/class_data_parser_tests/class_data_parser_tests.h"

void add_cross_class_lib_tests(CU_pSuite test_suite) {
  add_class_data_parser_tests(test_suite);
  add_data_parser_tests(test_suite);
  add_version_tests(test_suite);
}
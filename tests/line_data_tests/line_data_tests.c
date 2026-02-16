#include "./line_data_tests.h"
#include "../../src/Data/line_data.h"
#include <CUnit/Basic.h>
#include <CUnit/CUError.h>
#include <time.h>

void test_line_data_equality() {
  struct Line_Data a = {.indentation = 4, .left = "int", .right = "count"};
  struct Line_Data b = {.indentation = 4, .left = "int", .right = "count"};
  struct Line_Data c = {.indentation = 0, .left = "char *", .right = "buffer"};

  CU_ASSERT_TRUE(line_data_equality(&a, &b));
  CU_ASSERT_FALSE(line_data_equality(&a, &c));
  CU_ASSERT_TRUE(line_data_equality(NULL, NULL));
  CU_ASSERT_FALSE(line_data_equality(&a, NULL));
}

void add_line_data_tests(CU_pSuite test_suite) {
  CU_add_test(test_suite, "Test Line Data Equality", test_line_data_equality);
}

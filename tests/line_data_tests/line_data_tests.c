#include "./line_data_tests.h"
#include "../../src/Data/line_data.h"
#include <CUnit/Basic.h>
#include <CUnit/CUError.h>
#include <time.h>

void test_line_data_equality() {
  struct Line_Data original = {.indentation = 4, .left = "int", .right = "count"};
  struct Line_Data copy = {.indentation = 4, .left = "int", .right = "count"};
  struct Line_Data bad_indentation = {.indentation = 0, .left = "int", .right = "count"};
  struct Line_Data bad_left = {.indentation = 4, .left = "char *", .right = "count"};
  struct Line_Data bad_right = {.indentation = 4, .left = "int", .right = "buffer"};

  CU_ASSERT_TRUE(line_data_equality(&original, &original));

  CU_ASSERT_TRUE(line_data_equality(NULL, NULL));
  CU_ASSERT_FALSE(line_data_equality(&original, NULL));

  CU_ASSERT_TRUE(line_data_equality(&original, &copy));
  CU_ASSERT_FALSE(line_data_equality(&original, &bad_indentation));
  CU_ASSERT_FALSE(line_data_equality(&original, &bad_left));
  CU_ASSERT_FALSE(line_data_equality(&original, &bad_right));

  delete_data(original);
  delete_data(copy);
  delete_data(bad_indentation);
  delete_data(bad_left);
  delete_data(bad_right);
}

void add_line_data_tests(CU_pSuite test_suite) {
  CU_add_test(test_suite, "Test Line Data Equality", test_line_data_equality);
}

#include "./version_tests.h"
#include "version.h"
#include <CUnit/CUnit.h>
#include <stdlib.h>
#include <string.h>

void test_version_to_str_returns_string_representation() {
  // Arrange
  struct Version version = {.major = 1, .minor = 12, .patch = 1432};

  // Act
  char *result = malloc(sizeof(char) * 10);
  strncpy(result, version_to_str(&version), 9);
  result[9] = '\0';

  // Assert
  CU_ASSERT_TRUE(strncmp(result, "1.12.1432", 10) == 0);
}

void test_version_to_str_returns_null_if_version_is_null() {
  // Act
  char *result = version_to_str(NULL);

  // Assert
  CU_ASSERT_PTR_NULL(result);
}

void add_version_tests(CU_pSuite test_suite) {
  CU_ADD_TEST(test_suite, test_version_to_str_returns_string_representation);
  CU_ADD_TEST(test_suite, test_version_to_str_returns_null_if_version_is_null);
}
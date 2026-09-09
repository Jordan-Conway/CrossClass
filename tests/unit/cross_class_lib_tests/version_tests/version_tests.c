#include "./version_tests.h"
#include "version.h"
#include <CUnit/CUnit.h>
#include <CUnit/TestDB.h>
#include <stdlib.h>
#include <string.h>

void test_ensure_version_supported_higher_version_returns_false() {
  // Arrange
  struct Version current_version = get_current_version();

  struct Version higher_major = {.major = current_version.major + 10,
                                 .minor = current_version.minor,
                                 .patch = current_version.patch};
  struct Version higher_minor = {.major = current_version.major,
                                 .minor = current_version.minor + 10,
                                 .patch = current_version.patch};

  // Act
  bool higher_major_result = ensure_version_supported(&higher_major);
  bool higher_minor_result = ensure_version_supported(&higher_minor);

  // Assert
  CU_ASSERT_FALSE(higher_major_result);
  CU_ASSERT_FALSE(higher_minor_result);
}

void test_ensure_version_supported_current_version_returns_true() {
  // Arrange
  struct Version current_version = get_current_version();

  // Act
  bool result = ensure_version_supported(&current_version);

  // Assert
  CU_ASSERT_TRUE(result);
}

void test_ensure_version_patch_is_ignored() {
  // Arrange
  struct Version current_version = get_current_version();
  current_version.patch += 10;

  // Act
  bool result = ensure_version_supported(&current_version);

  // Assert
  CU_ASSERT_TRUE(result);
}

void test_version_to_str_returns_string_representation() {
  // Arrange
  struct Version version = {.major = 1, .minor = 12, .patch = 1432};

  // Act
  char *result = version_to_str(&version);

  // Assert
  CU_ASSERT_TRUE(strncmp(result, "1.12.1432", 10) == 0);

  free(result);
}

void test_version_to_str_returns_null_if_version_is_null() {
  // Act
  char *result = version_to_str(NULL);

  // Assert
  CU_ASSERT_PTR_NULL(result);
}

void add_version_tests(CU_pSuite test_suite) {
  CU_ADD_TEST(test_suite,
              test_ensure_version_supported_higher_version_returns_false);
  CU_ADD_TEST(test_suite,
              test_ensure_version_supported_current_version_returns_true);
  CU_ADD_TEST(test_suite, test_ensure_version_patch_is_ignored);
  CU_ADD_TEST(test_suite, test_version_to_str_returns_string_representation);
  CU_ADD_TEST(test_suite, test_version_to_str_returns_null_if_version_is_null);
}
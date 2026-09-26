#include "typescript_transpiler_tests.h"
#include "class_info.h"
#include "field.h"
#include "tokens.h"
#include "transpilers/typescript_transpiler.h"
#include <CUnit/CUnit.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <transpilers/transpiler.h>

void assert_lines_are(const struct Transpiled_Line *line, int num_lines, ...) {
  va_list args;
  va_start(args, num_lines);

  for (int i = 0; i < num_lines; i++) {
    char *expected_line = va_arg(args, char *);
    if (line->data == NULL) {
      CU_ASSERT_TRUE(expected_line == NULL);
    } else {
      CU_ASSERT_TRUE(strcmp(line->data, expected_line) == 0);
    }
    line = line->next;
  }

  CU_ASSERT_PTR_NULL(line);
}

void test_transpiles_valid_class_info(void) {
  // Arrange
  struct Field first_field = {
      .name = "first_field", .data_type = DATA_BOOL, .equitable = true};
  struct Field second_field = {
      .name = "second field", .data_type = DATA_DOUBLE, .equitable = true};
  struct Field third_field = {
      .name = "Third_Field", .data_type = DATA_DATETIME, .equitable = true};
  struct Field fourth_field = {
      .name = "fourth_field", .data_type = DATA_INT32, .equitable = false};
  struct Field_List fourth_field_node = {.data = &fourth_field};
  struct Field_List third_field_node = {.data = &third_field,
                                        .next = &fourth_field_node};
  struct Field_List second_field_node = {.data = &second_field,
                                         .next = &third_field_node};
  struct Field_List first_field_node = {.data = &first_field,
                                        .next = &second_field_node};

  struct Class_Info class_info = {.name = "My_Typescript_Type",
                                  .fields = &first_field_node};

  // Act
  struct Transpiled_Line *result = transpile_typescript(&class_info);

  // Assert
  const int expected_line_count = 12;

  assert_lines_are(
      result, expected_line_count, "export type My_Typescript_Type = {",
      "    first_field: boolean;", "    second field: number;",
      "    Third_Field: Date;", "    fourth_field: number;", "}", NULL,
      "export function My_Typescript_Type_equals(obj1: "
      "My_Typescript_Type, obj2: My_Typescript_Type) {",
      "    obj1.first_field == obj2.first_field &&",
      "    obj1.second field == obj2.second field &&",
      "    obj1.Third_Field == obj2.Third_Field", "}");

  for (int i = 0; i < expected_line_count; i++) {
    result = result->next;
  }
  CU_ASSERT_PTR_NULL(result);
}

void add_typescript_transpiler_tests(CU_pSuite test_suite) {
  CU_ADD_TEST(test_suite, test_transpiles_valid_class_info);
}
#include "typescript_transpiler_tests.h"
#include "class_info.h"
#include "field.h"
#include "tokens.h"
#include "transpilers/typescript_transpiler.h"
#include <string.h>

void test_transpiles_valid_class_info() {
  // Arrange
  struct Field first_field = {.name = "first_field", .data_type = DATA_BOOL};
  struct Field second_field = {.name = "second field",
                               .data_type = DATA_DOUBLE};
  struct Field third_field = {.name = "Third_Field",
                              .data_type = DATA_DATETIME};
  struct Field_List third_field_node = {.data = &third_field};
  struct Field_List second_field_node = {.data = &second_field,
                                         .next = &third_field_node};
  struct Field_List first_field_node = {.data = &first_field,
                                        .next = &second_field_node};

  struct Class_Info class_info = {.name = "My_Typescript_Type",
                                  .fields = &first_field_node};

  // Act
  struct Transpiled_Line *result = transpile_typescript(&class_info);

  // Assert
  CU_ASSERT_TRUE(strcmp(result->data, "export type My_Typescript_Type = {") ==
                 0);
  result = result->next;
  CU_ASSERT_TRUE(strcmp(result->data, "    first_field: boolean;") == 0);
  result = result->next;
  CU_ASSERT_TRUE(strcmp(result->data, "    second field: number;") == 0);
  result = result->next;
  CU_ASSERT_TRUE(strcmp(result->data, "    Third_Field: Date;") == 0);
  result = result->next;
  CU_ASSERT_TRUE(strcmp(result->data, "}") == 0);
  result = result->next;

  CU_ASSERT_PTR_NULL(result);
}

void add_typescript_transpiler_tests(CU_pSuite test_suite) {
  CU_ADD_TEST(test_suite, test_transpiles_valid_class_info);
}
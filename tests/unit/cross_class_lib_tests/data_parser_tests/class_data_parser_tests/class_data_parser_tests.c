#include "./class_data_parser_tests.h"

#include "ccx_line_data.h"
#include "class_info.h"
#include "data_parser.h"
#include "field.h"
#include "parsers/class_data_parser.h"
#include "tokens.h"
#include "version.h"
#include <CUnit/CUnit.h>
#include <CUnit/TestDB.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

struct Version create_default_version() {
  struct Version version = {.major = 0, .minor = 0, .patch = 1};
  return version;
}

static struct Data_Parser_Result create_default_result() {
  struct Data_Parser_Result result = {
      .is_error = false, .error_message = NULL, .result = NULL};
  return result;
}

static void append_line(struct Line_Data_Node **tail, char *left, char *right,
                        int indentation) {
  (*tail)->next = malloc(sizeof(typeof(*((*tail)->next))));
  struct Line_Data_Node *new_line = (*tail)->next;
  new_line->data = malloc(sizeof(typeof((*new_line->data))));
  new_line->data->left = left;
  new_line->data->right = right;
  new_line->data->indentation = indentation;
  new_line->next = NULL;
  new_line->prev = *tail;
  *tail = new_line;
}

void assert_parse_success(bool parsed,
                          const struct Data_Parser_Result *result) {
  CU_ASSERT(parsed == true);
  CU_ASSERT_PTR_NOT_NULL(result->result);
  CU_ASSERT_FALSE(result->is_error);
  CU_ASSERT_PTR_NULL(result->error_message);
}

void assert_field_equality(const struct Field *expected,
                           const struct Field *actual) {
  CU_ASSERT(strcmp(expected->name, actual->name) == 0);
  CU_ASSERT(expected->data_type == actual->data_type);
  CU_ASSERT(expected->store_type == actual->store_type);
  CU_ASSERT(expected->isConstant == actual->isConstant);
  CU_ASSERT(expected->visibility == actual->visibility);
}

void test_class_data_parser_no_details_returns_default_values() {
  struct Version version = create_default_version();
  struct Data_Parser_Result result = create_default_result();

  bool parsed = try_parse_class_data(NULL, &result, &version);
  assert_parse_success(parsed, &result);

  struct Class_Info *class_info = result.result;

  CU_ASSERT_PTR_NULL(class_info->name);
  CU_ASSERT(class_info->equality->type == EQUAL_BY_REFERENCE);
  CU_ASSERT_PTR_NULL(class_info->equality->excluded_fields);
  CU_ASSERT_PTR_NULL(class_info->fields);
  CU_ASSERT(class_info->visibility == VISIBILITY_NOT_SET);

  free(class_info);
}

void test_class_data_parser_name_is_parsed() {
  struct Version version = create_default_version();
  struct Data_Parser_Result result = create_default_result();
  struct Line_Data *line_data =
      (struct Line_Data *)malloc(sizeof(typeof(*line_data)));
  line_data->left = "name";
  line_data->right = "test_name";
  line_data->indentation = 0;
  struct Line_Data_Node line = {.prev = NULL, .next = NULL, .data = line_data};

  bool parsed = try_parse_class_data(&line, &result, &version);
  assert_parse_success(parsed, &result);

  struct Class_Info *class_info = result.result;

  CU_ASSERT(strcmp(class_info->name, "test_name") == 0);

  free(line_data);
  free(class_info);
}

void test_class_data_parser_visibilty_is_parsed() {
  struct Version version = create_default_version();
  struct Data_Parser_Result result = create_default_result();
  struct Line_Data *line_data =
      (struct Line_Data *)malloc(sizeof(typeof(*line_data)));
  line_data->left = "visibility";
  line_data->right = "public";
  line_data->indentation = 0;
  struct Line_Data_Node line = {.prev = NULL, .next = NULL, .data = line_data};

  bool parsed = try_parse_class_data(&line, &result, &version);
  assert_parse_success(parsed, &result);

  struct Class_Info *class_info = result.result;

  CU_ASSERT(class_info->visibility == VISIBILITY_PUBLIC);

  free(line_data);
  free(class_info);
}

void test_class_data_parser_equality_is_parsed() {
  struct Version version = create_default_version();
  struct Data_Parser_Result result = create_default_result();
  struct Line_Data *line_data =
      (struct Line_Data *)malloc(sizeof(typeof(*line_data)));
  line_data->left = "equality";
  line_data->right = "ref";
  line_data->indentation = 0;
  struct Line_Data_Node line = {.prev = NULL, .next = NULL, .data = line_data};

  bool parsed = try_parse_class_data(&line, &result, &version);
  assert_parse_success(parsed, &result);

  CU_ASSERT(result.result->equality->type == EQUAL_BY_REFERENCE);
  CU_ASSERT(result.result->equality->excluded_fields == NULL);

  free(line_data);
}

void test_class_data_parser_fields_are_parsed() {
  // Arrange
  struct Version version = create_default_version();
  struct Data_Parser_Result result = create_default_result();

  struct Line_Data fields_line_data = {
      .indentation = 0, .left = "fields", .right = ""};

  struct Line_Data_Node *line_data_list =
      malloc(sizeof(typeof(*line_data_list)));
  line_data_list->data = &fields_line_data;
  line_data_list->next = NULL;
  line_data_list->prev = NULL;
  append_line(&line_data_list, "field", "", 4);
  append_line(&line_data_list, "name", "id", 8);
  append_line(&line_data_list, "type", "string", 8);
  append_line(&line_data_list, "visibility", "public", 8);
  append_line(&line_data_list, "const", "false", 8);
  append_line(&line_data_list, "store", "ref", 8);
  while (line_data_list->prev != NULL) {
    line_data_list = line_data_list->prev;
  }
  struct Field expectedField = {.name = "id",
                                .data_type = DATA_STRING,
                                .visibility = VISIBILITY_PUBLIC,
                                .isConstant = false,
                                .store_type = STORETYPE_STORE_BY_REFERENCE};

  // Act
  bool parsed = try_parse_class_data(line_data_list, &result, &version);

  // Assert
  assert_parse_success(parsed, &result);

  struct Class_Info parsed_class = *result.result;
  CU_ASSERT(parsed_class.name == NULL);
  CU_ASSERT_PTR_NOT_NULL(parsed_class.fields);
  struct Field *id_field = parsed_class.fields->data;
  CU_ASSERT(strcmp(id_field->name, expectedField.name) == 0);
  CU_ASSERT(id_field->data_type == expectedField.data_type);
  CU_ASSERT(id_field->visibility == expectedField.visibility);

  // Cleanup
  while (line_data_list->next != NULL) {
    line_data_list = line_data_list->next;
  }
  while (line_data_list->prev != NULL) {
    line_data_list = line_data_list->prev;
    free(line_data_list->next);
  }
  free(line_data_list);
}

void add_class_data_parser_tests(CU_pSuite test_suite) {
  CU_ADD_TEST(test_suite,
              test_class_data_parser_no_details_returns_default_values);
  CU_ADD_TEST(test_suite, test_class_data_parser_name_is_parsed);
  CU_ADD_TEST(test_suite, test_class_data_parser_visibilty_is_parsed);
  CU_ADD_TEST(test_suite, test_class_data_parser_equality_is_parsed);
  CU_ADD_TEST(test_suite, test_class_data_parser_fields_are_parsed);
}
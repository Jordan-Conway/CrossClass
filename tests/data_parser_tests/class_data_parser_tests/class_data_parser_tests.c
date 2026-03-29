#include "./class_data_parser_tests.h"

#include "../../../src/Data/version.h"
#include "DataParser/Parsers/ClassDataParsers/class_data_parser.h"
#include "DataParser/data_parser_result.h"
#include "class_info.h"
#include "equality_type.h"
#include "line_data.h"
#include "line_data_list.h"
#include "store_type.h"
#include "visability.h"
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

struct Version create_default_version() {
    struct Version version = {
        .major = 0,
        .minor = 0,
        .patch = 1
    };
    return version;
}

static struct Data_Parser_Result create_default_result() {
    struct Data_Parser_Result result = {
        .is_error = false,
        .error_message = NULL,
        .result = NULL
    };
    return result;
}

void assert_parse_success(bool parsed, const struct Data_Parser_Result* result) {
    CU_ASSERT(parsed == true);
    CU_ASSERT_PTR_NOT_NULL(result->result);
    CU_ASSERT_FALSE(result->is_error);
    CU_ASSERT_PTR_NULL(result->error_message);
}

void test_class_data_parser_no_details_returns_default_values() {
    struct Version version = create_default_version();
    struct Data_Parser_Result result = create_default_result();

    bool parsed = try_parse_class_data(NULL, &result, &version);
    assert_parse_success(parsed, &result);

    struct Class_Info* class_info = result.result;

    CU_ASSERT_PTR_NULL(class_info->name);
    CU_ASSERT(class_info->equality->type == EQUAL_BY_REFERENCE);
    CU_ASSERT_PTR_NULL(class_info->equality->excluded_fields);
    CU_ASSERT_PTR_NULL(class_info->fields);
    CU_ASSERT(class_info->store_type == STORETYPE_NOT_SET);
    CU_ASSERT(class_info->visability == VISABILITY_NOT_SET);

    free(class_info);
}

void test_class_data_parser_name_is_parsed() {
    struct Version version = create_default_version();
    struct Data_Parser_Result result = create_default_result();
    struct Line_Data* line_data = (struct Line_Data*)malloc(sizeof(typeof(*line_data)));
    line_data->left = "name";
    line_data->right = "test_name";
    line_data->indentation = 0;
    struct Line_Data_Node line = {
        .prev = NULL,
        .next = NULL,
        .data = line_data
    };

    bool parsed = try_parse_class_data(&line, &result, &version);
    assert_parse_success(parsed, &result);

    struct Class_Info* class_info = result.result;

    CU_ASSERT(strcmp(class_info->name, "test_name") == 0);

    free(line_data);
    free(class_info);
}

void test_class_data_parser_visabilty_is_parsed() {
    struct Version version = create_default_version();
    struct Data_Parser_Result result = create_default_result();
    struct Line_Data* line_data = (struct Line_Data*)malloc(sizeof(typeof(*line_data)));
    line_data->left = "visability";
    line_data->right = "public";
    line_data->indentation = 0;
    struct Line_Data_Node line = {
        .prev = NULL,
        .next = NULL,
        .data = line_data
    };

    bool parsed = try_parse_class_data(&line, &result, &version);
    assert_parse_success(parsed, &result);

    struct Class_Info* class_info = result.result;

    CU_ASSERT(class_info->visability == VISABILITY_PUBLIC);

    free(line_data);
    free(class_info);
}

void add_class_data_parser_tests(CU_pSuite test_suite) {
    CU_ADD_TEST(test_suite, test_class_data_parser_no_details_returns_default_values);
    CU_ADD_TEST(test_suite, test_class_data_parser_name_is_parsed);
    CU_ADD_TEST(test_suite, test_class_data_parser_visabilty_is_parsed);
}
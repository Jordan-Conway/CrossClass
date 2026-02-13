#include "./data_parser_tests.h"

#include <CUnit/CUnit.h>
#include <CUnit/TestDB.h>
#include "../../src/DataParser/data_parser_result.h"
#include "../../src/DataParser/data_parser.h"
#include "../../src/line_data_list.h"
#include "line_data.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

struct Line_Data* create_default_line_data() {
    struct Line_Data* line = (struct Line_Data*)malloc(sizeof(struct Line_Data));
    line->indentation = 0;
    line->left = (char*)malloc(100* sizeof(char));
    line->right = (char*)malloc(100* sizeof(char));

    return line;
}

void test_parse_lines_no_version_fails() {
    struct Line_Data* line = create_default_line_data();
    strcpy(line->left, "not a version");
    strcpy(line->right, "0.1");

    struct Line_Data_Node* line_list = append_line_data(NULL, line);
    struct Data_Parser_Result* result = parse_line_data(line_list);

    CU_ASSERT(result->is_error == true);
    CU_ASSERT(result->result == NULL);
    CU_ASSERT(result->error_message != NULL);

    delete_list(line_list);
    delete_data_parser_result(result);
}

void test_parse_lines_no_type_fails() {
    struct Line_Data* line1 = create_default_line_data();
    struct Line_Data* line2 = create_default_line_data();

    strcpy(line1->left, "version");
    strcpy(line1->right, "0.1");
    strcpy(line1->left, "not a type");
    strcpy(line1->right, "class");

    struct Line_Data_Node* lines = append_line_data(NULL, line1);
    lines = append_line_data(lines, line2);

    struct Data_Parser_Result* result = parse_line_data(lines);

    CU_ASSERT(result->is_error == true);
    CU_ASSERT(result->result == NULL);
    CU_ASSERT(result->error_message != NULL);

    delete_list(lines);
    delete_data_parser_result(result);
}

void test_parse_lines_unsupported_type_fails() {

}

void add_data_parser_tests(CU_pSuite test_suite) {
    CU_add_test(test_suite, "Test parse_lines with no version fails", test_parse_lines_no_version_fails);
    CU_add_test(test_suite, "Test parse_lines with no type fails", test_parse_lines_no_type_fails);
    CU_add_test(test_suite, "Test parse_lines with unsupported type fails", test_parse_lines_unsupported_type_fails);
}
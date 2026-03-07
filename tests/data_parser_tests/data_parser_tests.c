#include "./data_parser_tests.h"
#include "DataParser/data_parser_result.h"
#include "../DataParser/data_parser.h"
#include "data_reader.h"
#include "line_data_list.h"
#include <CUnit/CUnit.h>
#include <CUnit/TestDB.h>
#include <stdio.h>
#include <stdlib.h>

void test_data_reader_missing_version_fails() {
    FILE* test_file = tmpfile();

    fputs("Not a version: 0.0.1\n", test_file);
    rewind(test_file);

    struct Line_Data_Node* lines = read_ccd_file(test_file);
    struct Data_Parser_Result* result = parse_line_data(lines);

    CU_ASSERT_PTR_NOT_NULL(lines);
    CU_ASSERT_PTR_NOT_NULL(result);
    CU_ASSERT(result->result == NULL);
    CU_ASSERT(result->is_error = true);
    CU_ASSERT_PTR_NOT_NULL(result->error_message);

    free(result);
    delete_list(lines);
    fclose(test_file);
}

void test_data_reader_version_not_first_fails() {
    FILE* test_file = tmpfile();

    fputs("Not a version: 0.0.1", test_file);
    fputs("version: 0.0.1", test_file);
    rewind(test_file);

    struct Line_Data_Node* lines = read_ccd_file(test_file);
    struct Data_Parser_Result* result = parse_line_data(lines);

    CU_ASSERT_PTR_NOT_NULL(lines);

    CU_ASSERT(result->result == NULL);
    CU_ASSERT(result->is_error == true);
    CU_ASSERT_PTR_NOT_NULL(result->error_message);

    printf("Result is null: %d\n", result == NULL);
    free(result);
    delete_list(lines);

    fclose(test_file);
}

void add_data_parser_tests(CU_pSuite test_suite) {
    CU_ADD_TEST(test_suite, test_data_reader_missing_version_fails);
    CU_ADD_TEST(test_suite, test_data_reader_version_not_first_fails);
}
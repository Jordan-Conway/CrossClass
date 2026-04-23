#include "./data_parser_tests.h"
#include "../../src/DataParser/data_parser_result.h"
#include "../../src/DataParser/data_parser.h"
#include "../../src/data_reader.h"
#include "../../src/line_data_list.h"
#include <CUnit/CUnit.h>
#include <CUnit/TestDB.h>
#include <stdio.h>
#include <stdlib.h>

// Generic function to test for an error
void test_error_raised(const char source_func[], const int source_line, FILE* test_file){
    const int pre_call_errors = CU_get_number_of_tests_failed();
    
    struct Line_Data_Node* lines = read_ccd_file(test_file);
    struct Data_Parser_Result* result = parse_line_data(lines);

    CU_ASSERT_PTR_NOT_NULL(lines);
    CU_ASSERT_PTR_NOT_NULL(result);
    CU_ASSERT(result->result == NULL);
    CU_ASSERT(result->is_error == true);
    CU_ASSERT_PTR_NOT_NULL(result->error_message);

    const int post_call_errors = CU_get_number_of_tests_failed();

    if(post_call_errors > pre_call_errors){
        printf("FAIL OCCURRED - Called in %s - On line %d\n", source_func, source_line);
    }

    free(result);
    delete_list(lines);
}

void test_data_reader_missing_version_fails() {
    FILE* test_file = tmpfile();

    fputs("Not a version: 0.0.1\n", test_file);
    rewind(test_file);

    test_error_raised(__func__, __LINE__, test_file);

    fclose(test_file);
}

void test_data_reader_version_not_first_fails() {
    FILE* test_file = tmpfile();

    fputs("Not a version: 0.0.1", test_file);
    fputs("version: 0.0.1", test_file);
    rewind(test_file);

    test_error_raised(__func__, __LINE__, test_file);

    fclose(test_file);
}

void test_data_reader_version_malformed_fails() {
    FILE* test_file = tmpfile();

    fputs("version:0.1", test_file);
    rewind(test_file);

    test_error_raised(__func__, __LINE__, test_file);

    fclose(test_file);
}

void test_data_reader_version_extra_content_fails() {
    FILE* test_file = tmpfile();

    fputs("version:0.0.1.2", test_file);
    rewind(test_file);

    test_error_raised(__func__, __LINE__, test_file);

    fclose(test_file);
}

void test_data_reader_missing_type_fails() {
    FILE* test_file = tmpfile();

    fputs("version:0.0.1", test_file);
    fputs("Not a type: type", test_file);
    rewind(test_file);

    test_error_raised(__func__, __LINE__, test_file);

    fclose(test_file);
}


void test_data_reader_unsupported_type_fails() {
    FILE* test_file = tmpfile();

    fputs("version:0.0.1", test_file);
    fputs("type: unsupported", test_file);
    rewind(test_file);

    test_error_raised(__func__, __LINE__, test_file);

    fclose(test_file);
}

void add_data_parser_tests(CU_pSuite test_suite) {
    CU_ADD_TEST(test_suite, test_data_reader_missing_version_fails);
    CU_ADD_TEST(test_suite, test_data_reader_version_not_first_fails);
    CU_ADD_TEST(test_suite, test_data_reader_version_malformed_fails);
    CU_ADD_TEST(test_suite, test_data_reader_version_extra_content_fails);
    CU_ADD_TEST(test_suite, test_data_reader_missing_type_fails);
    CU_ADD_TEST(test_suite, test_data_reader_unsupported_type_fails);
}
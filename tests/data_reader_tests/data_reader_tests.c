#include "./data_reader_tests.h"

#include "../../src/data_reader.h"
#include "../../src/line_data_list.h"
#include <CUnit/CUnit.h>
#include <CUnit/TestDB.h>
#include <stdio.h>
#include <string.h>

void test_read_ccd_file(){
    FILE* file = tmpfile();

    fputs("version:0.1\n", file);
    fputs("// This is a comment\n", file);
    fputs("type:class\n", file);
    fputs("name:test\n", file);

    rewind(file);

    struct Line_Data_Node* lines = read_ccd_file(file);

    printf("Beginning asserts\n");

    CU_ASSERT_PTR_NOT_NULL(lines);
    CU_ASSERT_PTR_NOT_NULL(lines->data);
    CU_ASSERT(strcmp(lines->data->left, "version") == 0);
    CU_ASSERT(strcmp(lines->data->right, "0.1") == 0);

    CU_ASSERT_PTR_NOT_NULL(lines->next);
    CU_ASSERT_PTR_NOT_NULL(lines->next->data);
    CU_ASSERT(strcmp(lines->next->data->left, "type") == 0);
    CU_ASSERT(strcmp(lines->next->data->right, "class") == 0);

    CU_ASSERT_PTR_NOT_NULL(lines->next);
    CU_ASSERT_PTR_NOT_NULL(lines->next->data);
    CU_ASSERT(strcmp(lines->next->next->data->left, "name") == 0);
    CU_ASSERT(strcmp(lines->next->next->data->right, "test") == 0);

    CU_ASSERT_PTR_NULL(lines->next->next->next);

    delete_list(lines);

    fclose(file);
}

void add_data_reader_tests(CU_pSuite test_suite) {
    CU_ADD_TEST(test_suite, test_read_ccd_file);
}
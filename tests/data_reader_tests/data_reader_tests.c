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
    fputs("name: test\n", file);
    fputs("fields:\n", file);
    fputs("    test_field:\n", file);
    fputs("        type:   int32", file);

    rewind(file);

    struct Line_Data_Node* lines = read_ccd_file(file);

    printf("Beginning asserts\n");

    CU_ASSERT_PTR_NOT_NULL(lines);
    CU_ASSERT_PTR_NOT_NULL(lines->data);
    CU_ASSERT(strcmp(lines->data->left, "version") == 0);
    CU_ASSERT(strcmp(lines->data->right, "0.1") == 0);
    CU_ASSERT(lines->data->indentation == 0);

    lines = lines->next;

    CU_ASSERT_PTR_NOT_NULL(lines);
    CU_ASSERT_PTR_NOT_NULL(lines->data);
    CU_ASSERT(strcmp(lines->data->left, "type") == 0);
    CU_ASSERT(strcmp(lines->data->right, "class") == 0);
    CU_ASSERT(lines->data->indentation == 0);

    lines = lines->next;

    CU_ASSERT_PTR_NOT_NULL(lines);
    CU_ASSERT_PTR_NOT_NULL(lines->data);
    CU_ASSERT(strcmp(lines->data->left, "name") == 0);
    CU_ASSERT(strcmp(lines->data->right, "test") == 0);
    CU_ASSERT(lines->data->indentation == 0);

    lines = lines->next;

    CU_ASSERT_PTR_NOT_NULL(lines);
    CU_ASSERT_PTR_NOT_NULL(lines->data);
    CU_ASSERT(strcmp(lines->data->left, "fields") == 0);
    CU_ASSERT(strcmp(lines->data->right, "") == 0);
    CU_ASSERT(lines->data->indentation == 0);

    lines = lines->next;

    CU_ASSERT_PTR_NOT_NULL(lines);
    CU_ASSERT_PTR_NOT_NULL(lines->data);
    CU_ASSERT(strcmp(lines->data->left, "test_field") == 0);
    CU_ASSERT(strcmp(lines->data->right, "") == 0);
    CU_ASSERT(lines->data->indentation == 4);

    lines = lines->next;

    CU_ASSERT_PTR_NOT_NULL(lines);
    CU_ASSERT_PTR_NOT_NULL(lines->data);
    CU_ASSERT(strcmp(lines->data->left, "type") == 0);
    printf("%s\n", lines->data->right);
    CU_ASSERT(strcmp(lines->data->right, "int32") == 0);
    CU_ASSERT(lines->data->indentation == 8);

    CU_ASSERT_PTR_NULL(lines->next);

    delete_list(lines);

    fclose(file);
}

void test_read_ccd_file_handle_spaces() {
    FILE* file = tmpfile();

    fputs("ver sion:0 .1", file);

    rewind(file);

    struct Line_Data_Node* lines = read_ccd_file(file);

    CU_ASSERT_PTR_NOT_NULL(lines);
    CU_ASSERT_PTR_NOT_NULL(lines->data);
    CU_ASSERT(strcmp("ver sion", lines->data->left) == 0);
    CU_ASSERT(strcmp("0 .1", lines->data->right) == 0);
    CU_ASSERT(lines->data->indentation == 0);
    printf("Indent: %d\n", lines->data->indentation);
    CU_ASSERT_PTR_NULL(lines->next);
}

void add_data_reader_tests(CU_pSuite test_suite) {
    CU_ADD_TEST(test_suite, test_read_ccd_file);
    CU_ADD_TEST(test_suite, test_read_ccd_file_handle_spaces);
}
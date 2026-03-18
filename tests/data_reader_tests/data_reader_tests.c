#include "./data_reader_tests.h"

#include "../../src/data_reader.h"
#include "../../src/line_data_list.h"
#include <CUnit/CUnit.h>
#include <CUnit/TestDB.h>
#include <stdio.h>
#include <string.h>

// Generic function to test a whole line
void test_line(struct Line_Data_Node* lines, char expected_left[], char expected_right[], int expected_indentation){
    CU_ASSERT_PTR_NOT_NULL(lines);
    CU_ASSERT_PTR_NOT_NULL(lines->data);
    CU_ASSERT(strcmp(lines->data->left, expected_left) == 0);
    CU_ASSERT(strcmp(lines->data->right, expected_right) == 0);
    CU_ASSERT(lines->data->indentation == expected_indentation);
}

void test_read_ccd_file(){
    FILE* file = tmpfile();

    fputs("version:0.1\n", file);
    fputs("// This is a comment\n", file);
    fputs("type:class\n", file);
    fputs("\n   \n", file); // Test for whitespace
    fputs("name: test\n", file);
    fputs("fields:\n", file);
    fputs("    test_field:\n", file);
    fputs("        type:   int32", file);

    rewind(file);

    struct Line_Data_Node* lines = read_ccd_file(file);

    printf("Beginning asserts\n");
    test_line(lines, "version", "0.1", 0);
    lines = lines->next;

    test_line(lines, "type", "class", 0);
    lines = lines->next;

    test_line(lines, "name", "test", 0);
    lines = lines->next;

    test_line(lines, "fields", "", 0);
    lines = lines->next;

    test_line(lines, "test_field", "", 4);
    lines = lines->next;

    test_line(lines, "type", "int32", 8);
    CU_ASSERT_PTR_NULL(lines->next);

    delete_list(lines);

    fclose(file);
}

void test_read_ccd_file_handle_spaces() {
    FILE* file = tmpfile();

    fputs("ver sion:0 .1", file);

    rewind(file);

    struct Line_Data_Node* lines = read_ccd_file(file);

    test_line(lines, "ver sion", "0 .1", 0);
    printf("Indent: %d\n", lines->data->indentation);
    CU_ASSERT_PTR_NULL(lines->next);

    delete_list(lines);

    fclose(file);
}

void test_read_ccd_file_lowercase_left(){
    FILE* file = tmpfile();

    fputs("lowercase left:lowercase right\n", file);
    fputs("lowercase left:UpPeRcAsE right\n", file);
    fputs("UpPeRcAsE left:lowercase right\n", file);
    fputs("UpPeRcAsE left:UpPeRcAsE right\n", file);

    rewind(file);

    struct Line_Data_Node* lines = read_ccd_file(file);

    printf("Beginning asserts\n");
    test_line(lines, "lowercase left", "lowercase right", 0);
    lines = lines->next;

    test_line(lines, "lowercase left", "UpPeRcAsE right", 0);
    lines = lines->next;

    test_line(lines, "uppercase left", "lowercase right", 0);
    lines = lines->next;

    test_line(lines, "uppercase left", "UpPeRcAsE right", 0);
    CU_ASSERT_PTR_NULL(lines->next);

    delete_list(lines);

    fclose(file);
}

void add_data_reader_tests(CU_pSuite test_suite) {
    CU_ADD_TEST(test_suite, test_read_ccd_file);
    CU_ADD_TEST(test_suite, test_read_ccd_file_handle_spaces);
    CU_ADD_TEST(test_suite, test_read_ccd_file_lowercase_left);
}

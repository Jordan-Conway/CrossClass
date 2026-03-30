#include "./data_reader_tests.h"

#include "../../src/data_reader.h"
#include "../../src/line_data_list.h"
#include <CUnit/CUnit.h>
#include <CUnit/TestDB.h>
#include <stdio.h>
#include <string.h>

int known_failed_tests = 0;
int* failed_tests_ptr;

// Generic function to test a whole line
void test_line(const char source_func[], const int source_line, struct Line_Data_Node* lines, char expected_left[], char expected_right[], int expected_indentation){
    CU_ASSERT_PTR_NOT_NULL(lines);
    CU_ASSERT_PTR_NOT_NULL(lines->data);
    CU_ASSERT(strcmp(lines->data->left, expected_left) == 0);
    CU_ASSERT(strcmp(lines->data->right, expected_right) == 0);
    CU_ASSERT(lines->data->indentation == expected_indentation);

    if(*failed_tests_ptr > known_failed_tests){
        printf("FAIL OCCURRED - Called in %s - On line %d\n", source_func, source_line);
        known_failed_tests++; // Allows for multiple tests to be caught
    }
}

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
    test_line(__func__, __LINE__, lines, "version", "0.1", 0);
    lines = lines->next;

    test_line(__func__, __LINE__, lines, "type", "class", 0);
    lines = lines->next;

    test_line(__func__, __LINE__, lines, "name", "test", 0);
    lines = lines->next;

    test_line(__func__, __LINE__, lines, "fields", "", 0);
    lines = lines->next;

    test_line(__func__, __LINE__, lines, "test_field", "", 4);
    lines = lines->next;

    test_line(__func__, __LINE__, lines, "type", "int32", 8);
    CU_ASSERT_PTR_NULL(lines->next);

    delete_list(lines);

    fclose(file);
}

void test_read_ccd_file_handle_spaces() {
    FILE* file = tmpfile();

    fputs("ver sion:0 .1", file);

    rewind(file);

    struct Line_Data_Node* lines = read_ccd_file(file);

    test_line(__func__, __LINE__, lines, "ver sion", "0 .1", 0);
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
    test_line(__func__, __LINE__, lines, "lowercase left", "lowercase right", 0);
    lines = lines->next;

    test_line(__func__, __LINE__, lines, "lowercase left", "UpPeRcAsE right", 0);
    lines = lines->next;

    test_line(__func__, __LINE__, lines, "uppercase left", "lowercase right", 0);
    lines = lines->next;

    test_line(__func__, __LINE__, lines, "uppercase left", "UpPeRcAsE right", 0);
    CU_ASSERT_PTR_NULL(lines->next);

    delete_list(lines);

    fclose(file);
}

void test_trailing_whitespace_is_trimmed(){
    FILE* file = tmpfile();

    fputs("nothing trailing:nothing trailing\n", file);
    fputs("trailing left   :nothing trailing\n", file);
    fputs("nothing trailing:trailing right  \n", file);
    fputs("trailing left  :trailing right   \n", file);
    fputs("empty right nothing trailing: \n", file);
    fputs("empty right trailing left :    \n", file);

    rewind(file);

    struct Line_Data_Node* lines = read_ccd_file(file);

    printf("Beginning asserts\n");
    test_line(__func__, __LINE__, lines, "nothing trailing", "nothing trailing", 0);
    lines = lines->next;

    test_line(__func__, __LINE__, lines, "trailing left", "nothing trailing", 0);
    lines = lines->next;

    test_line(__func__, __LINE__, lines, "nothing trailing", "trailing right", 0);
    lines = lines->next;

    test_line(__func__, __LINE__, lines, "trailing left", "trailing right", 0);
    lines = lines->next;
    
    test_line(__func__, __LINE__, lines, "empty right nothing trailing", "", 0);
    lines = lines->next;

    test_line(__func__, __LINE__, lines, "empty right trailing left", "", 0);
    CU_ASSERT_PTR_NULL(lines->next);

    delete_list(lines);

    fclose(file);
}

void test_arbitrary_line_lengths(){
    const char long_string = { [0 ... 99] = 'a', [100] = '\0'};

    FILE* file = tmpfile();

    fputs("short left:short right\n", file);
    // "a...a:short right"
    fputs(long_string, file);
    fputs(":short right\n", file);
    // "short left:a...a"
    fputs("short left:", file);
    fputs(long_string, file);
    fputs("\n", file);
    // "a...a:a...a"
    fputs(long_string, file);
    fputs(":", file);
    fputs(long_string, file);
    fputs("\n", file);
    
    rewind(file);

    struct Line_Data_Node* lines = read_ccd_file(file);

    // Remember, left side will be lowercase
    printf("Beginning asserts\n");
    test_line(__func__, __LINE__, lines, "short left", "short right", 0);
    lines = lines->next;

    test_line(__func__, __LINE__, lines, long_string, "short right", 0);
    lines = lines->next;

    test_line(__func__, __LINE__, lines, "short left", long_string, 0);
    lines = lines->next;

    test_line(__func__, __LINE__, lines, long_string, long_string, 0);
    CU_ASSERT_PTR_NULL(lines->next);

    delete_list(lines);

    fclose(file);
}

void add_data_reader_tests(CU_pSuite test_suite) {
    failed_tests_ptr = &CU_get_registry()->uiNumberOfTests;
    CU_ADD_TEST(test_suite, test_read_ccd_file);
    CU_ADD_TEST(test_suite, test_read_ccd_file_handle_spaces);
    CU_ADD_TEST(test_suite, test_read_ccd_file_lowercase_left);
    CU_ADD_TEST(test_suite, test_trailing_whitespace_is_trimmed);
    CU_ADD_TEST(test_suite, test_arbitrary_line_lengths);
}

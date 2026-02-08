#include "./line_data_list_tests.h"

#include "../../src/line_data_list.h"
#include <CUnit/Basic.h>
#include <CUnit/CUError.h>
#include <CUnit/CUnit.h>
#include <CUnit/TestDB.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct Line_Data_Node* list = NULL;

struct Line_Data* create_empty_line_data() {
    struct Line_Data* data = (struct Line_Data*)calloc(1, sizeof(struct Line_Data));
    data->left = NULL;
    data->right = NULL;

    return data;
}

void test_create_line_data_list() {
    list = create_line_data_list();
    struct Line_Data_Node* expected_list = (struct Line_Data_Node*)calloc(1, sizeof(struct Line_Data_Node));
    expected_list->data = NULL;
    expected_list->prev = NULL;
    expected_list->next = NULL;

    CU_ASSERT(list != NULL)
    CU_ASSERT(list->data == expected_list->data);
    CU_ASSERT(list->prev == expected_list->prev);
    CU_ASSERT(list->next == expected_list->next);

    delete_list(list);
    delete_list(expected_list);
}

void test_append_line_data() {
    list = create_line_data_list();

    struct Line_Data* line_data_1 = create_empty_line_data();
    line_data_1->left = (char*)malloc(100 * sizeof(char));
    line_data_1->right = (char*)malloc(100 * sizeof(char));
    strncpy(line_data_1->left, "version", 8);
    strncpy(line_data_1->right, "0.1", 4);

    struct Line_Data_Node* new_tail = append_line_data(list, line_data_1);

    CU_ASSERT(list->data == NULL);
    CU_ASSERT(list->next == new_tail);
    CU_ASSERT(list->prev == NULL);

    CU_ASSERT(new_tail->prev == list);
    CU_ASSERT(new_tail->data == line_data_1);
    CU_ASSERT(new_tail->next == NULL);

    struct Line_Data* line_data_2 = (struct Line_Data*)calloc(1, sizeof(struct Line_Data));
    line_data_2->left = (char*)malloc(100 * sizeof(char));
    line_data_2->right = (char*)malloc(100 * sizeof(char));

    new_tail = append_line_data(list, line_data_2);
    CU_ASSERT(new_tail->prev == list->next);
    CU_ASSERT(new_tail->data == line_data_2);
    CU_ASSERT(new_tail->next == NULL);

    delete_list(list);
}

void test_get_head_of_line_data_list() {
    list = create_line_data_list();

    struct Line_Data* data1 = create_empty_line_data();
    struct Line_Data* data2 = create_empty_line_data();

    append_line_data(list, data1);
    list = append_line_data(list, data2);

    list = get_head_of_line_data_list(list);

    CU_ASSERT(list->data == NULL);
    CU_ASSERT(list->prev == NULL);
    CU_ASSERT(list->next->next != NULL);
    CU_ASSERT(list->next->next->next == NULL);
    
    delete_list(list);
}  

int run_line_data_list_tests() {
    CU_pSuite test_suite = NULL;

    if (CU_initialize_registry() != CUE_SUCCESS){
        return CU_get_error();
    }

    test_suite = CU_add_suite("Line Data List Tests Suite", NULL, NULL);

    if (test_suite == NULL) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    CU_add_test(test_suite, "Test Create Line Data List", test_create_line_data_list);
    CU_add_test(test_suite, "Test Append Line Data", test_append_line_data);
    CU_add_test(test_suite, "Test Get Head of Line Data List", test_get_head_of_line_data_list);

    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();

    return CU_get_error();
}

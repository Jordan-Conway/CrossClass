#include "./line_data_list_tests.h"

#include "../../src/line_data_list.h"
#include "line_data.h"
#include <CUnit/Basic.h>
#include <CUnit/CUError.h>
#include <CUnit/TestDB.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct Line_Data_Node* list = NULL;

struct Line_Data* create_empty_line_data() {
    struct Line_Data* data = (struct Line_Data*)calloc(1, sizeof(struct Line_Data));
    data->left = (char*)malloc(100* sizeof(char));
    data->right = (char*)malloc(100* sizeof(char));
    data->indentation = 0;

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
    line_data_1->indentation = 0;
    strcpy(line_data_1->left, "version");
    strcpy(line_data_1->right, "0.1");

    struct Line_Data_Node* new_tail = append_line_data(list, line_data_1);

    CU_ASSERT(list->data == NULL);
    CU_ASSERT(list->next == new_tail);
    CU_ASSERT(list->prev == NULL);

    CU_ASSERT(new_tail->prev == list);
    CU_ASSERT(strcmp(new_tail->data->left, "version") == 0);
    CU_ASSERT(strcmp(new_tail->data->right, "0.1") == 0);
    CU_ASSERT(new_tail->next == NULL);

    struct Line_Data* line_data_2 = (struct Line_Data*)calloc(1, sizeof(struct Line_Data));
    line_data_2->left = NULL;
    line_data_2->right = NULL;
    line_data_2->indentation = 0;

    new_tail = append_line_data(list, line_data_2);
    CU_ASSERT(new_tail->prev == list->next);
    CU_ASSERT(new_tail->data->left == NULL);
    CU_ASSERT(new_tail->data->right == NULL);
    CU_ASSERT(new_tail->next == NULL);

    delete_list(list);
}

void test_append_line_data_null_head() {
    struct Line_Data_Node* head = NULL;

    struct Line_Data* line_data = create_empty_line_data();
    strcpy(line_data->left, "Hello");
    strcpy(line_data->right, "World");

    head = append_line_data(head, line_data);

    CU_ASSERT(head != NULL);
    CU_ASSERT(strcmp(head->data->left, "Hello") == 0);
    CU_ASSERT(strcmp(head->data->right, "World") == 0);
    CU_ASSERT(head->data->indentation == 0);
    CU_ASSERT_PTR_NULL(head->prev);
    CU_ASSERT_PTR_NULL(head->next);
    
    delete_list(head);
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


void test_line_data_node_equality(void) {
    struct Line_Data a_data = { .indentation = 4, .left = "int",  .right = "count" };
    struct Line_Data b_data = { .indentation = 4, .left = "int",  .right = "count" };
    struct Line_Data c_data = { .indentation = 0, .left = "char", .right = "buffer" };

    struct Line_Data_Node a = { .data = &a_data, .next = NULL, .prev = NULL };
    struct Line_Data_Node b = { .data = &b_data, .next = NULL, .prev = NULL };
    struct Line_Data_Node c = { .data = &c_data, .next = NULL, .prev = NULL };

    CU_ASSERT_TRUE(line_data_node_equality(&a, &b));
    CU_ASSERT_FALSE(line_data_node_equality(&a, &c));
    CU_ASSERT_TRUE(line_data_node_equality(&a, &a));
    CU_ASSERT_TRUE(line_data_node_equality(NULL, NULL));
    CU_ASSERT_FALSE(line_data_node_equality(&a, NULL));
}

void add_line_data_list_tests(CU_pSuite test_suite) {
    CU_add_test(test_suite, "Test Create Line Data List", test_create_line_data_list);
    CU_add_test(test_suite, "Test Append Line Data", test_append_line_data);
    CU_add_test(test_suite, "Test Append Line Data with Null Head", test_append_line_data_null_head);
    CU_add_test(test_suite, "Test Get Head of Line Data List", test_get_head_of_line_data_list);
    CU_add_test(test_suite, "Test Line Data Node Equality", test_line_data_node_equality);
}

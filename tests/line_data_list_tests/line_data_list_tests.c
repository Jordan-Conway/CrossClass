#include "./line_data_list_tests.h"

#include "../../src/line_data_list.h"
#include <CUnit/Basic.h>
#include <CUnit/CUError.h>
#include <CUnit/CUnit.h>
#include <CUnit/TestDB.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct Line_Data_Node* list = NULL;

int init_line_data_list_tests_suite(){
    list = create_line_data_list();

    return 0;
}

int clean_line_data_list_tests_suite(){
    delete_list(list);
    free(list);
    return 0;
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

    free(expected_list);
}

int run_line_data_list_tests() {
    CU_pSuite test_suite = NULL;

    if (CU_initialize_registry() != CUE_SUCCESS){
        return CU_get_error();
    }

    test_suite = CU_add_suite("Line Data List Tests Suite", init_line_data_list_tests_suite, clean_line_data_list_tests_suite);

    if (test_suite == NULL) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    CU_add_test(test_suite, "test_create_line_data_list", test_create_line_data_list);

    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();

    return CU_get_error();
}

#include "./data_reader_tests/data_reader_tests.h"
#include "./line_data_list_tests/line_data_list_tests.h"
#include <CUnit/Basic.h>
#include <CUnit/TestDB.h>
#include <CUnit/TestRun.h>
#include <stdio.h>

int main() {
    CU_pSuite test_suite = NULL;

    if (CU_initialize_registry() != CUE_SUCCESS){
        return CU_get_error();
    }

    test_suite = CU_add_suite("CrossClass Test Suite", NULL, NULL);

    if (test_suite == NULL) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    add_line_data_list_tests(test_suite);
    add_data_reader_tests(test_suite);

    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();

    int num_run = CU_get_number_of_tests_run();
    int num_failed = CU_get_number_of_tests_failed();

    CU_cleanup_registry();

    printf("%d of %d tests passed.\n", num_run - num_failed, num_run);

    if (num_failed == 0) {
        return 0;
    }

    return 1;
}
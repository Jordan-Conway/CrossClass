#include "./transpiler_tests.h"
#include "typescript_transpiler_tests.h"

void add_transpiler_tests(CU_pSuite test_suite) {
  add_typescript_transpiler_tests(test_suite);
}
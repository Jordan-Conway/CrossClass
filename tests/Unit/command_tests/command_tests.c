#include "./command_tests.h"
#include "Commands/HelpCommand/help_command.h"
#include "Commands/command.h"
#include "Commands/command_list.h"
#include <CUnit/CUnit.h>

void parse_help_short_command_success() {
    int argc = 0;
    char* argv[] = {"-h"};

    struct Command_Data* result = parse_command(argc,  argv);

    CU_ASSERT(result->command_function == help_command);
    CU_ASSERT(result->type == VC_HELP);
}

void parse_help_long_command_success() {
    int argc = 0;
    char* argv[] = {"--help"};

    struct Command_Data* result = parse_command(argc,  argv);

    CU_ASSERT(result->command_function == help_command);
    CU_ASSERT(result->type == VC_HELP);
}

void add_command_tests(CU_pSuite test_suite) {
    CU_ADD_TEST(test_suite, parse_help_short_command_success);
    CU_ADD_TEST(test_suite, parse_help_long_command_success);
}
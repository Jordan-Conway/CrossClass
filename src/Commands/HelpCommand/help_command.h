#ifndef HELP_COMMAND
#define HELP_COMMAND

#include "../command.h"
#include <stdbool.h>

bool validate_help_command_args(int argc, char* argv[]);

/*
    Prints the help page
*/
enum command_result help_command(int argc, char* argv[]);

#endif
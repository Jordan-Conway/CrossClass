#ifndef VERSION_COMMAND
#define VERSION_COMMAND

#include "../command.h"
#include <stdbool.h>

bool validate_version_command_args(int argc, char* argv[]);

/*
    Prints the current version
*/
struct command_result version_command(int argc, char* argv[]);

#endif
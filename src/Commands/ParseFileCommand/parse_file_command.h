#ifndef PARSE_FILE_COMMAND
#define PARSE_FILE_COMMAND

#include "../command.h"
#include <stdbool.h>

bool validate_parse_command_args(int argc, char* argv[]);

/*
    Parses a given ccd file
*/
enum command_result parse_file_command(int argc, char* argv[]);

#endif
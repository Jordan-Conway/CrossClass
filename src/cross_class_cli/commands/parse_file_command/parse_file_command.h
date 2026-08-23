#ifndef PARSE_FILE_COMMAND
#define PARSE_FILE_COMMAND

#include "../command.h"
#include <stdbool.h>

/*
    Parses a given ccd file
*/
struct Command_Result parse_file_command(int argc, char *argv[]);

#endif
#ifndef COMMAND_LIST
#define COMMAND_LIST

#include "./HelpCommand/help_command.h"
#include <stdlib.h>

enum valid_command {
    VC_HELP,
    VC_NOT_SET
};

struct Command_Data {
    enum command_result (*command_function)(int, char*[]);
    enum valid_command type;
};

extern struct Command_Data Invalid_Command_Data;
extern struct Command_Data Help_Command_Data;

#endif
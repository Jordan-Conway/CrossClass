#include "./command_list.h"

struct Command_Data Help_Command_Data = {
    .command_function = help_command,
    .type = VC_HELP
};

struct Command_Data Invalid_Command_Data = {
    .command_function = NULL,
    .type = VC_NOT_SET
};
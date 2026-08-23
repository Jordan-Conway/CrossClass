#include "./command_list.h"
#include "./help_command/help_command.h"
#include "./parse_file_command/parse_file_command.h"
#include "./version_command/version_command.h"
#include <stdbool.h>
#include <stdlib.h>

bool default_validate_args(int, char **) { return true; }

struct Command_Data Help_Command_Data = {.command_function = help_command,
                                         .type = VC_HELP,
                                         .validate_args =
                                             &default_validate_args};

struct Command_Data Parse_File_Command_Data = {
    .command_function = parse_file_command,
    .type = VC_PARSE_FILE,
    .validate_args = &default_validate_args};

struct Command_Data Invalid_Command_Data = {.command_function = NULL,
                                            .type = VC_NOT_SET,
                                            .validate_args =
                                                &default_validate_args};

struct Command_Data Version_Command_Data = {.command_function = version_command,
                                            .type = VC_VERSION,
                                            .validate_args =
                                                &default_validate_args};
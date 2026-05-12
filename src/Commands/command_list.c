#include "./command_list.h"
#include "./HelpCommand/help_command.h"
#include "./VersionCommand/version_command.h"
#include "Commands/ParseFileCommand/parse_file_command.h"
#include <stdlib.h>

struct Command_Data Help_Command_Data = {
    .command_function = help_command,
    .type = VC_HELP
};

struct Command_Data Parse_File_Command_Data = {
    .command_function = parse_file_command,
    .type = VC_PARSE_FILE
};

struct Command_Data Invalid_Command_Data = {
    .command_function = NULL,
    .type = VC_NOT_SET
};

struct Command_Data Version_Command_Data = {
    .command_function = version_command,
    .type = VC_VERSION
};
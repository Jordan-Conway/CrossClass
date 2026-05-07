#include "./command.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./command_list.h"

bool args_are_valid(struct Command_Data* command, int argc, char* argv[]) {
    if(command->type == VC_HELP) {
        return true;
    }

    if(command->type == VC_VERSION) {
        return true;
    }

    return true;
}

struct Command_Data* parse_command(int* argc, char** argv[]) {
    struct Command_Data* result = (typeof(result))malloc(sizeof(*result));
    result->command_function = NULL;
    if(
        *argc == 0 ||
        strcmp((*argv)[0], "-h") == 0 ||
        strcmp((*argv)[0], "--help") == 0
    ) {
        result = &Help_Command_Data;
        goto parsed;
    }

    if(
        strcmp((*argv)[0], "-v") == 0 ||
        strcmp((*argv)[0], "--version") == 0
    ) {
        result = &Version_Command_Data;
        goto parsed;
    }

    // If we haven't got a valid command, we should return the help command
    if(!result->command_function) {
        result = &Help_Command_Data;
    }

parsed:
    if(!args_are_valid(result, *argc, *argv)) {
        result = &Invalid_Command_Data;
    }

    return result;
}
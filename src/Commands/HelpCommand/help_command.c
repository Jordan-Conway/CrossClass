#include "./help_command.h"
#include "Commands/command.h"
#include <stdio.h>

struct command_result help_command(int argc, char* argv[]) {
    printf("TODO: Add help here\n");

    struct command_result result = {
        .status = COMMAND_RESULT_SUCCESS,
        .message = "Ok"
    };

    return result;
}
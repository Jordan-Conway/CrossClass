#include "./version_command.h"
#include "../../version.h"
#include "Commands/command.h"
#include <stdio.h>

struct command_result version_command(int argc, char* argv[]) {
    struct Version version = get_current_version();
    printf("%d.%d.%d\n", version.major, version.minor, version.patch);
    
    struct command_result result = {
        .status = COMMAND_RESULT_SUCCESS,
        .message = "Ok"
    };

    return result;
}
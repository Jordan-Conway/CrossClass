#include "./version_command.h"
#include "../../version.h"
#include "Commands/command.h"
#include <stdio.h>

enum command_result version_command(int argc, char* argv[]) {
    struct Version version = get_current_version();
    printf("%d.%d.%d\n", version.major, version.minor, version.patch);
    return COMMAND_RESULT_SUCCESS;
}
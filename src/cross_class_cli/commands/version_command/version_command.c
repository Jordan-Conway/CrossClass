#include "./version_command.h"
#include "../../shared_macros.h"
#include "../command.h"
#include "version.h"
#include <stdio.h>

struct Command_Result version_command(int argc, char **argv) {
  UNUSED(argc);
  UNUSED(argv);

  struct Version version = get_current_version();
  printf("%d.%d.%d\n", version.major, version.minor, version.patch);

  struct Command_Result result = {.status = COMMAND_RESULT_SUCCESS,
                                  .message = "Ok"};

  return result;
}
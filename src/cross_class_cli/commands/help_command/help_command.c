#include "./help_command.h"
#include "../command.h"
#include <stdio.h>

struct Command_Result help_command(int, char **) {
  printf("TODO: Add help here\n");

  struct Command_Result result = {.status = COMMAND_RESULT_SUCCESS,
                                  .message = "Ok"};

  return result;
}
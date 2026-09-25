#include "./list_transpilers_command.h"

#include "../../shared_macros.h"
#include <stdio.h>

struct Command_Result list_transpiler_command(int argc, char *argv[]) {
  UNUSED(argc);
  UNUSED(argv);

  printf("Transpilers:\n");
  printf("Typescript: ts\n");

  struct Command_Result result = {.status = COMMAND_RESULT_SUCCESS,
                                  .message = NULL};

  return result;
}
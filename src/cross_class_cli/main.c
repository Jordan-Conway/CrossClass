#include "./commands/command.h"
#include "./commands/command_list.h"

int main(int argc, char *argv[]) {

  argc--;
  argv++;

  struct Command_Data *command = parse_command(argc, argv);
  struct Command_Result result = command->command_function(argc, argv);

  return result.status;
}

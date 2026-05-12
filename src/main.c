#include "../Commands/command_list.h"
#include "../Commands/command.h"

int main(int argc, char* argv[]) {

    argc--;
    argv++;

    struct Command_Data* command = parse_command(argc, argv);
    struct command_result result = command->command_function(argc, argv);

    return result.status;
}
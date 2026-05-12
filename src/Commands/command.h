#ifndef COMMAND
#define COMMAND

enum command_status {
    COMMAND_RESULT_FAILURE = 0,
    COMMAND_RESULT_SUCCESS = 1
};

struct command_result {
    enum command_status status;
    char* message;
};

/*
    Parses program arguments to generate a command.
*/
struct Command_Data* parse_command(int argc, char* argv[]);

#endif
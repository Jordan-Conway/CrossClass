#ifndef COMMAND
#define COMMAND

enum command_status {
    COMMAND_RESULT_SUCCESS = 0,
    COMMAND_RESULT_FAILURE = 1,
    COMMAND_RESULT_NOT_SET = 2,
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
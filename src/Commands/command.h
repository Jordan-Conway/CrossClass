#ifndef COMMAND
#define COMMAND

enum command_result {
    COMMAND_RESULT_FAILURE = 0,
    COMMAND_RESULT_SUCCESS = 1
};

/*
    Parses program arguments to generate a command.
*/
struct Command_Data* parse_command(int* argc, char** argv[]);

#endif
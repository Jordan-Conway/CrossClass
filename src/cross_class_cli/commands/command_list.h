#ifndef COMMAND_LIST
#define COMMAND_LIST

enum valid_command {
    VC_HELP,
    VC_PARSE_FILE,
    VC_VERSION,
    VC_NOT_SET
};

struct Command_Data {
    struct command_result (*command_function)(int, char*[]);
    enum valid_command type;
};

extern struct Command_Data Invalid_Command_Data;
extern struct Command_Data Help_Command_Data;
extern struct Command_Data Parse_File_Command_Data;
extern struct Command_Data Version_Command_Data;

#endif
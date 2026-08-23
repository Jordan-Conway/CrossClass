#ifndef COMMAND_LIST
#define COMMAND_LIST

#include <stdbool.h>
enum ValidCommand { VC_HELP, VC_PARSE_FILE, VC_VERSION, VC_NOT_SET };

struct Command_Data {
  struct Command_Result (*command_function)(int, char *[]);
  enum ValidCommand type;
  bool (*validate_args)(int argc, char *argv[]);
};

extern struct Command_Data Invalid_Command_Data;
extern struct Command_Data Help_Command_Data;
extern struct Command_Data Parse_File_Command_Data;
extern struct Command_Data Version_Command_Data;

#endif
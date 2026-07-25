#ifndef DATA_PARSER
#define DATA_PARSER

#include "ccx_line_data.h"
#include <stdbool.h>

struct Data_Parser_Result {
  struct Class_Info *result;
  bool is_error;
  char *error_message;
};

struct Data_Parser_Result *
parse_line_data(struct Line_Data_Node *line_data_list);

#endif
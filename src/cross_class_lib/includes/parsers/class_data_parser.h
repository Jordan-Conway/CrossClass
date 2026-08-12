#ifndef CLASS_DATA_PARSER
#define CLASS_DATA_PARSER

#include "../data_parser.h"
#include "../version.h"
#include "ccx_line_data.h"
#include <stdbool.h>

struct Already_Set_Attributes {
  bool name_set;
  bool type_set;
  bool visibility_set;
  bool const_set;
  bool store_set;
};

struct Already_Set_Tokens {
    bool name_set;
    bool visibility_set;
    bool equality_set;
    bool fields_set;
};

bool try_parse_class_data(struct Line_Data_Node *line,
                          struct Data_Parser_Result *result,
                          const struct Version *version);

#endif
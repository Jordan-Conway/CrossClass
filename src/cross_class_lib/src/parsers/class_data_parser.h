#ifndef CLASS_DATA_PARSER
#define CLASS_DATA_PARSER

#include "../../includes/data_parser.h"
#include "../../includes/version.h"
#include "ccx_line_data.h"

bool try_parse_class_data(struct Line_Data_Node *line,
                          struct Data_Parser_Result *result,
                          const struct Version *version);

#endif
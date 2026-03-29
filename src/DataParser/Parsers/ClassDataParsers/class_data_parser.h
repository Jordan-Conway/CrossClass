#ifndef CLASS_DATA_PARSER
#define CLASS_DATA_PARSER

#include "DataParser/data_parser_result.h"
#include "line_data_list.h"
#include "version.h"

bool try_parse_class_data(struct Line_Data_Node* line, struct Data_Parser_Result* result, const struct Version* version);

#endif
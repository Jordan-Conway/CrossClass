#ifndef DATA_PARSER_RESULT
#define DATA_PARSER_RESULT

#include "class_info.h"
#include <stdbool.h>

struct Data_Parser_Result {
    struct Class_Info* result;
    bool is_error;
    char* error_message;
};

#endif
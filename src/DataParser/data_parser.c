#include "./data_parser.h"

#include "DataParser/data_parser_result.h"
#include "class_info.h"
#include "./Data/Tokens/equality_type.h"
#include "line_data_list.h"
#include "store_type.h"
#include "visability.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Data_Parser_Result* create_default_result() {
    struct Data_Parser_Result* result = (struct Data_Parser_Result*)malloc(sizeof(struct Data_Parser_Result));

    result->is_error = false;
    result->result = NULL;
    result->error_message = NULL;

    return result;
}

struct Class_Info* create_default_class() {
    struct Class_Info* class_info = (struct Class_Info*)malloc(sizeof(struct Class_Info));

    class_info->equality = (struct Equality*)malloc(sizeof(struct Equality));
    class_info->equality->type = BY_REFERENCE;
    class_info->equality->excluded_fields = NULL;

    class_info->fields = NULL;
    class_info->name = NULL;
    class_info->store_type = STORE_BY_VALUE;
    class_info->visability = PUBLIC;

    return class_info;
}

struct Data_Parser_Result* parse_line_data(struct Line_Data_Node* line_data_list){
    char* errorMessage = NULL;
    struct Data_Parser_Result* result = create_default_result();
    line_data_list = get_head_of_line_data_list(line_data_list);
    if (line_data_list == NULL) {
        asprintf(&result->error_message, "List with no data given to data parser");
        goto parse_failed;
    }
    if (strcmp(line_data_list->data->left, "version") != 0) {
        asprintf(&result->error_message, "Error: No version number found, instead found %s", line_data_list->data->left);
        goto parse_failed;
    }

    // TODO: Once ccd spec is finalised, use version to choose parsing
    line_data_list = line_data_list->next;

    if (strcmp(line_data_list->data->left, "type") != 0) {
        asprintf(&result->error_message, "Error: No type found, instead found %s", line_data_list->data->left);
        goto parse_failed;
    }

    if (strcmp(line_data_list->data->right, "class") != 0) {
        asprintf(&result->error_message, "Unsupported type found: %s\n", line_data_list->data->right);
        goto parse_failed;
    }

    struct Class_Info* class_info = create_default_class();

    goto success;

parse_failed:
    result->is_error = true;
    return result;

success:
    result->result = class_info;
    return result;
}
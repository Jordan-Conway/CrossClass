#include "./data_parser.h"

#include "DataParser/data_parser_result.h"
#include "line_data_list.h"
#include "object_type.h"
#include "version.h"
#include "./Parsers/ClassDataParsers/class_data_parser.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static struct Data_Parser_Result* create_default_result() {
    struct Data_Parser_Result* result = (struct Data_Parser_Result*)malloc(sizeof(struct Data_Parser_Result));

    result->is_error = false;
    result->result = NULL;
    result->error_message = NULL;

    return result;
}

struct Version* ensure_version(const struct Line_Data_Node* line) {
    printf("Getting version\n");
    if (strcmp("version", line->data->left) != 0) {
        printf("Expected to find version, instead found %s\n", line->data->left);
        return NULL;
    }
    printf("Left is version\n");
    char* version_string = line->data->right;

    if (strlen(version_string) != 6) {
        printf("Malformed version found. Version should be formatted as x.x.x, instead found %s\n", version_string);
        return NULL;
    }

    struct Version* version = malloc(sizeof(typeof(*version)));
    version->major = atoi(&version_string[0]);
    version->minor = atoi(&version_string[2]);
    version->patch = atoi(&version_string[4]);

    return version;
}

enum Object_Type get_object_type(const struct Line_Data_Node* line) {
    if(strcmp(line->data->left, "type") != 0) {
        printf("Expect type, instead found %s\n", line->data->left);
        return OBJECT_TYPE_NONE;
    }

    if(strcmp(line->data->right, "class") == 0) {
        return OBJECT_TYPE_CLASS;
    }

    printf("Expected supported type, instead found %s\n", line->data->right);
    return OBJECT_TYPE_NONE;
}

struct Data_Parser_Result* parse_line_data(struct Line_Data_Node* line_data_list){
    struct Data_Parser_Result* result = create_default_result();

    struct Version* version = ensure_version(line_data_list);
    if(!version) {
        result->is_error = true;
        result->error_message = "Version either missing or not found";
        goto failure;
    }
    line_data_list = line_data_list->next;

    enum Object_Type type = get_object_type(line_data_list);
    if(type == OBJECT_TYPE_NONE){
        result->is_error = true;
        result->error_message = "Type either missing or not found";
        goto failure;
    }
    line_data_list = line_data_list->next;

    bool parsed = false;
    switch (type) {
        case OBJECT_TYPE_CLASS:
            parsed = try_parse_class_data(line_data_list, result, version);
            break;
        default:
            parsed = false;
            break;
    }

    if (!parsed) {
        result->is_error = true;
        result->error_message = "Failed to parse";
        goto failure;
    }
    else{
        goto success;
    }

failure:
    free(result->result);
    result->result = NULL;
success:
    free(version);
    return result;
}
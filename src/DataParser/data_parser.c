#include "./data_parser.h"

#include "DataParser/data_parser_result.h"
#include "line_data_list.h"
#include "object_type.h"
#include "version.h"
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

    }
}

struct Data_Parser_Result* parse_line_data(struct Line_Data_Node* line_data_list){
    struct Data_Parser_Result* result = create_default_result();
    printf("Created default result\n");
    struct Version* version = ensure_version(line_data_list);
    printf("Got version\n");
    if(!version) {
        result->is_error = true;
        result->error_message = "Version either missing or not found";
        goto failure;
    }
    line_data_list = line_data_list->next;

failure:
    result->result = NULL;
success:
    free(version);
    return result;
}
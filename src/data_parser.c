#include "./data_parser.h"

#include "class_info.h"
#include "./Data/Tokens/equality_type.h"
#include "store_type.h"
#include "visability.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Class_Info* create_default_class() {
    struct Class_Info* class_info = (struct Class_Info*)malloc(sizeof(struct Class_Info));

    class_info->equality = (struct Equality*)malloc(sizeof(struct Equality));
    class_info->equality->type = BY_REFERENCE;
    class_info->equality->excluded_fields = NULL;

    class_info->fields = NULL;
    class_info->name = NULL;
    class_info->store_type = STORE_BY_VALUE;
    class_info->visability = PUBLIC;
}

struct Class_Info* parse_lines(struct Line_Data_Node* line_data_list){
    if (!line_data_list) {
        return NULL;
    }

    if (!strcmp(line_data_list->data->left, "version")) {
        goto missing_version;
    }

    // TODO: Once ccd spec is finalised, use version to choose parsing
    line_data_list = line_data_list->next;

    if (!strcmp(line_data_list->data->left, "type")) {
        goto missing_type;
    }

    if (!strcmp(line_data_list->data->right, "class")) {
        goto unsupported_type;
    }

    struct Class_Info* class_info = create_default_class();

    goto success;

missing_version:
    printf("Error: No version number found, instead found %s\n", line_data_list->data->left);
    exit(1);

missing_type:
    printf("Error: No type found, instead found %s\n", line_data_list->data->left);
    exit(1);

unsupported_type:
    printf("Unsupported type found: %s\n", line_data_list->data->right);
    exit(1);

success:
    return class_info;
}
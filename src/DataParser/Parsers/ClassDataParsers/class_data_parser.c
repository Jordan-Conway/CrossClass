#include "./class_data_parser.h"

#include "../../../Data/class_info.h"
#include "../../../line_data_list.h"
#include "../../../Data/Tokens/equality_type.h"
#include "../../../Data/Tokens/store_type.h"
#include "../../../Data/Tokens/visibility.h"
#include <stdlib.h>
#include <string.h>

struct Class_Info* create_default_class() {
    struct Class_Info* class_info = (struct Class_Info*)malloc(sizeof(struct Class_Info));

    class_info->equality = (struct Equality*)malloc(sizeof(struct Equality));
    class_info->equality->type = EQUAL_BY_REFERENCE;
    class_info->equality->excluded_fields = NULL;

    class_info->fields = NULL;
    class_info->name = NULL;
    class_info->store_type = STORETYPE_NOT_SET;
    class_info->visibility = VISIBILITY_NOT_SET;

    return class_info;
}

enum Visibility parse_visibility(char* value) {
    if (strcmp(value, "public") == 0) {
        return VISIBILITY_PUBLIC;
    }
    if (strcmp(value, "private") == 0) {
        return VISIBILITY_PRIVATE;
    }
    if (strcmp(value, "internal") == 0) {
        return VISIBILITY_INTERNAL;
    }

    return VISIBILITY_NOT_SET;
}

bool try_parse_class_data(struct Line_Data_Node* line, struct Data_Parser_Result* result, const struct Version* version) {
    struct Class_Info* class_info = create_default_class();

    while(line != NULL) {
        if(strcmp(line->data->left, "name") == 0) {
            class_info->name = line->data->right;
            goto next_line;
        }
        if(strcmp(line->data->left, "visibility") == 0) {
            class_info->visibility = parse_visibility(line->data->right);
            goto next_line;
        }

    next_line:
        line = line->next;
    }

    result->result = class_info;

    return true;
}
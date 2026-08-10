#include "../../includes/parsers/class_data_parser.h"

#include "../../includes/class_info.h"
#include "../../includes/tokens.h"
#include "ccx_line_data.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

struct Class_Info *create_default_class() {
  struct Class_Info *class_info =
      (struct Class_Info *)malloc(sizeof(struct Class_Info));

  class_info->equality = (struct Equality *)malloc(sizeof(struct Equality));
  class_info->equality->type = EQUAL_BY_REFERENCE;
  class_info->equality->excluded_fields = NULL;

  class_info->fields = NULL;
  class_info->name = NULL;
  class_info->visibility = VISIBILITY_NOT_SET;

  return class_info;
}

struct Field *create_default_field() {
  struct Field *field = malloc(sizeof(typeof(*field)));

  field->data_type = DATA_NOT_SET;
  field->store_type = STORETYPE_NOT_SET;
  field->isConstant = true;
  field->visibility = VISIBILITY_NOT_SET;

  return field;
}

struct Equality *create_default_equality() {
  struct Equality *equality = malloc(sizeof(typeof(*equality)));
  equality->type = EQUAL_NOT_SET;

  return equality;
}

bool str_to_bool(char *str) { return (strcmp(str, "true") == 0); }

struct Field *parse_field(struct Line_Data_Node **line) {
  int field_indentation = (*line)->data->indentation;
  struct Field *field = malloc(sizeof(typeof(*field)));

  bool attribute_seen[5] = { false, false, false, false, false };
  while (*line != NULL && (*line)->data->indentation == field_indentation) {
    char *field_property_name = (*line)->data->left;
    char *field_property_value = (*line)->data->right;
    if (strcmp(field_property_name, "name") == 0) {
      if(attribute_seen[0]){
        printf("Error: This field has multiple name attributes\n");
        return NULL;
      }
      field->name = field_property_value;
      attribute_seen[0] = true;
    } else if (strcmp(field_property_name, "type") == 0) {
      if(attribute_seen[1]){
        printf("Error: This field has multiple type attributes\n");
        return NULL;
      }
      field->data_type = data_type_from_str(field_property_value);
      attribute_seen[1] = true;
    } else if (strcmp(field_property_name, "visibility") == 0) {
      if(attribute_seen[2]){
        printf("Error: This field has multiple visibility attributes\n");
        return NULL;
      }
      field->visibility = visibility_from_str(field_property_value);
      attribute_seen[2] = true;
    } else if (strcmp(field_property_name, "const") == 0) {
      if(attribute_seen[3]){
        printf("Error: This field has multiple const attributes\n");
        return NULL;
      }
      field->isConstant = str_to_bool(field_property_value);
      attribute_seen[3] = true;
    } else if (strcmp(field_property_name, "store") == 0) {
      if(attribute_seen[4]){
        printf("Error: This field has multiple store attributes\n");
        return NULL;
      }
      field->store_type = store_type_from_str(field_property_value);
      attribute_seen[4] = true;
    }
    *line = (*line)->next;
  }

  return field;
}

struct Field_List *parse_fields(struct Line_Data_Node **line) {
  struct Field_List *result = malloc(sizeof(typeof(*result)));

  while (*line != NULL && strcmp((*line)->data->left, "field") == 0) {
    *line = (*line)->next;
    result->data = parse_field(line);
    if(result->data == NULL){
      return NULL;
    }

    result->next = malloc(sizeof(typeof(*result)));
    result->next->prev = result;
    result = result->next;
  }

  // We always allocate an extra field, so remove it here
  result = result->prev;
  free(result->next);
  result->next = NULL;

  return result;
}

bool try_parse_class_data(struct Line_Data_Node *line,
                          struct Data_Parser_Result *result,
                          const struct Version *version) {
  struct Class_Info *class_info = create_default_class();

  bool token_seen[4] = { false, false, false, false };
  while (line != NULL) {
    if (strcmp(line->data->left, "name") == 0) {
      if(token_seen[0]){
        printf("Error: This class has multiple name tokens");
        return false;
      }
      class_info->name = line->data->right;
      token_seen[0] = true;
    } else if (strcmp(line->data->left, "visibility") == 0) {
      if(token_seen[1]){
        printf("Error: This class has multiple visibility tokens");
        return false;
      }
      class_info->visibility = visibility_from_str(line->data->right);
      token_seen[1] = true;
    } else if (strcmp(line->data->left, "equality") == 0) {
      if(token_seen[2]){
        printf("Error: This class has multiple quality tokens");
        return false;
      }
      class_info->equality->type = equality_type_from_str(line->data->right);
      token_seen[2] = true;
    } else if (strcmp(line->data->left, "fields") == 0) {
      if(token_seen[3]){
        printf("Error: This class has multiple field lists - please combine them");
        return false;
      }
      line = line->next;
      class_info->fields = parse_fields(&line);
      if(class_info->fields == NULL){
        return false;
      }
      token_seen[3] = true;
    }

    if (line != NULL) {
      line = line->next;
    }
  }

  result->result = class_info;

  return true;
}
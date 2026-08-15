#include "../../includes/parsers/class_data_parser.h"

#include "../../includes/class_info.h"
#include "../../includes/tokens.h"
#include "ccx_line_data.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Already_Set_Field_Attributes {
  bool name_set;
  bool type_set;
  bool visibility_set;
  bool const_set;
  bool store_set;
};

struct Already_Set_Class_Attributes {
  bool name_set;
  bool visibility_set;
  bool equality_set;
  bool fields_set;
};

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

struct Already_Set_Field_Attributes *initialise_already_set_attributes() {
  struct Already_Set_Field_Attributes *asa =
      (struct Already_Set_Field_Attributes *)malloc(sizeof(typeof(*asa)));
  asa->name_set = false;
  asa->type_set = false;
  asa->visibility_set = false;
  asa->const_set = false;
  asa->store_set = false;

  return asa;
}

struct Already_Set_Class_Attributes *initialise_already_set_tokens() {
  struct Already_Set_Class_Attributes *ast =
      (struct Already_Set_Class_Attributes *)malloc(sizeof(typeof(*ast)));
  ast->name_set = false;
  ast->visibility_set = false;
  ast->equality_set = false;
  ast->fields_set = false;

  return ast;
}

bool str_to_bool(char *str) { return (strcmp(str, "true") == 0); }

struct Field *parse_field(struct Line_Data_Node **line) {
  int field_indentation = (*line)->data->indentation;
  struct Field *field = malloc(sizeof(typeof(*field)));

  struct Already_Set_Field_Attributes *already_set_attributes =
      initialise_already_set_attributes();
  while (*line != NULL && (*line)->data->indentation == field_indentation) {
    char *field_property_name = (*line)->data->left;
    char *field_property_value = (*line)->data->right;
    if (strcmp(field_property_name, "name") == 0) {
      if (already_set_attributes->name_set) {
        printf("ERROR: A field has multiple name attributes\n");
        goto rejected_field;
      }
      field->name = field_property_value;
      already_set_attributes->name_set = true;
    } else if (strcmp(field_property_name, "type") == 0) {
      if (already_set_attributes->type_set) {
        printf("ERROR: A field has multiple type attributes\n");
        goto rejected_field;
      }
      field->data_type = data_type_from_str(field_property_value);
      already_set_attributes->type_set = true;
    } else if (strcmp(field_property_name, "visibility") == 0) {
      if (already_set_attributes->visibility_set) {
        printf("ERROR: A field has multiple visibility attributes\n");
        goto rejected_field;
      }
      field->visibility = visibility_from_str(field_property_value);
      already_set_attributes->visibility_set = true;
    } else if (strcmp(field_property_name, "const") == 0) {
      if (already_set_attributes->const_set) {
        printf("ERROR: A field has multiple const attributes\n");
        goto rejected_field;
      }
      field->isConstant = str_to_bool(field_property_value);
      already_set_attributes->const_set = true;
    } else if (strcmp(field_property_name, "store") == 0) {
      if (already_set_attributes->store_set) {
        printf("ERROR: A field has multiple store attributes\n");
        goto rejected_field;
      }
      field->store_type = store_type_from_str(field_property_value);
      already_set_attributes->store_set = true;
    }
    *line = (*line)->next;
  }
  // If another line exists that wasn't empty, reconsider it
  if (*line != NULL) {
    *line = (*line)->prev;
  }

  free(already_set_attributes);

  return field;

rejected_field:
  free(already_set_attributes);
  free(field);
  return NULL;
}

struct Field_List *parse_fields(struct Line_Data_Node **line) {
  struct Field_List *result = malloc(sizeof(typeof(*result)));
  result->data = NULL;
  result->next = NULL;
  result->prev = NULL;
  struct Field_List *current_result = result;

  while (*line != NULL && strcmp((*line)->data->left, "field") == 0) {
    *line = (*line)->next;
    current_result->data = parse_field(line);
    if (current_result->data == NULL) { // Duplicate field attribute found
      // Cleanup heap data
      while (current_result->prev != NULL) {
        current_result = current_result->prev;
        free(current_result->next);
      }
      free(current_result);

      return NULL;
    };

    current_result->next = malloc(sizeof(typeof(*current_result)));
    current_result->next->prev = current_result;
    current_result = current_result->next;
  }

  // We always allocate an extra field, so remove it here
  current_result = current_result->prev;
  free(current_result->next);
  current_result->next = NULL;

  return result;
}

bool try_parse_class_data(struct Line_Data_Node *line,
                          struct Data_Parser_Result *result,
                          const struct Version *version) {
  struct Class_Info *class_info = create_default_class();

  struct Already_Set_Class_Attributes *already_set_tokens =
      initialise_already_set_tokens();
  while (line != NULL) {
    if (strcmp(line->data->left, "name") == 0) {
      if (already_set_tokens->name_set) {
        printf("ERROR: Class has multiple name tokens\n");
        goto rejected_class;
      }
      class_info->name = line->data->right;
      already_set_tokens->name_set = true;
    } else if (strcmp(line->data->left, "visibility") == 0) {
      if (already_set_tokens->visibility_set) {
        printf("ERROR: Class has multiple visibility tokens\n");
        goto rejected_class;
      }
      class_info->visibility = visibility_from_str(line->data->right);
      already_set_tokens->visibility_set = true;
    } else if (strcmp(line->data->left, "equality") == 0) {
      if (already_set_tokens->equality_set) {
        printf("ERROR: Class has multiple equality tokens\n");
        goto rejected_class;
      }
      class_info->equality->type = equality_type_from_str(line->data->right);
      already_set_tokens->equality_set = true;
    } else if (strcmp(line->data->left, "fields") == 0) {
      if (already_set_tokens->fields_set) {
        printf("ERROR: Class has multiple field lists - please merge them\n");
        goto rejected_class;
      }
      line = line->next;
      class_info->fields = parse_fields(&line);
      if (class_info->fields == NULL) {
        goto rejected_class;
      }
      already_set_tokens->fields_set = true;
    }

    if (line != NULL) {
      line = line->next;
    }
  }

  result->result = class_info;

  free(already_set_tokens);

  return true;

rejected_class:
  free(already_set_tokens);
  free(class_info);
  return false;
}
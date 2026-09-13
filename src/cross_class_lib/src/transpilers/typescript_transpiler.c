#include "../../includes/transpilers/typescript_transpiler.h"
#include "class_info.h"
#include "tokens.h"
#include "transpilers/transpiler.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define APPEND_TO_LINE(line_ptr, string, string_length)                        \
  strncpy(*line_ptr, string, string_length);                                   \
  *line_ptr = *line_ptr + string_length;

// This will be configurable at some point
const int indentation = 4;

static const char *export_type_string = "export type ";
static const int export_type_length = 12;
static const char *post_type_name_suffix_string = " = {";
static const int post_type_name_suffix_length = 4;

static const char *export_function_string = "export function ";
static const int export_function_length = 16;
static const char *equals_function_start_string = "_equals(obj1: ";
static const int equals_function_start_length = 14;
static const char *equals_function_middle_string = ", obj2: ";
static const int equals_function_middle_length = 8;
static const char *equals_function_end_string = ") {";
static const int equals_function_end_length = 3;

bool is_last_field_for_equality(struct Field_List *field) {
  field = field->next;
  while (field != NULL) {
    if (field->data->equitable) {
      return false;
    }
    field = field->next;
  }

  return true;
}

struct Transpiled_Line *next_line(struct Transpiled_Line *current_line) {
  struct Transpiled_Line *next_line = malloc(sizeof(typeof(*next_line)));
  next_line->next = NULL;
  next_line->data = NULL;
  next_line->prev = current_line;

  if (current_line != NULL) {
    current_line->next = next_line;
  }

  return next_line;
}

char *data_type_to_typescript_type(enum DataType type) {
  switch (type) {
  case DATA_CHAR:
  case DATA_STRING:
    return "string";
  case DATA_INT8:
  case DATA_INT16:
  case DATA_INT32:
  case DATA_INT64:
  case DATA_INT128:
  case DATA_FLOAT:
  case DATA_DOUBLE:
  case DATA_LONG_DOUBLE:
    return "number";
  case DATA_BOOL:
    return "boolean";
  case DATA_DATE:
  case DATA_TIME:
  case DATA_DATETIME:
    return "Date";
  default:
    // TODO: Replace with actual type at some point
    printf("Encountered unknown type %d\n", type);
    return "";
  }
}

char *create_type_declaration_line(const char *type_name) {
  // export type <type_name> = {
  int type_name_length = strlen(type_name);
  int type_line_length =
      type_name_length + export_type_length + post_type_name_suffix_length + 1;

  char *line = malloc(sizeof(char) * type_line_length);
  char *line_ptr = line;

  APPEND_TO_LINE(&line_ptr, export_type_string, export_type_length);
  APPEND_TO_LINE(&line_ptr, type_name, type_name_length);
  APPEND_TO_LINE(&line_ptr, post_type_name_suffix_string,
                 post_type_name_suffix_length);
  *line_ptr = '\0';

  return line;
}

void create_equality_function(struct Transpiled_Line **current_line_ptr,
                              const struct Class_Info *class_info) {
  struct Transpiled_Line *current_line = next_line(*current_line_ptr);

  // export function <type>_equals(obj1: <type>, obj2: <type>) {\0
  const int type_name_length = strlen(class_info->name);
  current_line->data =
      malloc(sizeof(char) * (export_function_length + type_name_length +
                             equals_function_start_length + type_name_length +
                             equals_function_middle_length + type_name_length +
                             equals_function_end_length + 1));
  char *function_line_ptr = current_line->data;
  APPEND_TO_LINE(&function_line_ptr, export_function_string,
                 export_function_length);
  APPEND_TO_LINE(&function_line_ptr, class_info->name, type_name_length);
  APPEND_TO_LINE(&function_line_ptr, equals_function_start_string,
                 equals_function_start_length);
  APPEND_TO_LINE(&function_line_ptr, class_info->name, type_name_length);
  APPEND_TO_LINE(&function_line_ptr, equals_function_middle_string,
                 equals_function_middle_length);
  APPEND_TO_LINE(&function_line_ptr, class_info->name, type_name_length);
  APPEND_TO_LINE(&function_line_ptr, equals_function_end_string,
                 equals_function_end_length);
  *function_line_ptr = '\0';

  struct Field_List *current_field = class_info->fields;
  while (current_field != NULL) {
    if (current_field->data->equitable) {
      current_line = next_line(current_line);
      const int field_name_length = strlen(current_field->data->name);
      const bool is_last_field = is_last_field_for_equality(current_field);
      const int and_length = is_last_field ? 0 : 3;
      // <indentation>obj1.<field> == obj2.<field>[ &&]\0
      const int line_length = indentation + 5 + field_name_length + 9 +
                              field_name_length + and_length + 1;
      current_line->data = malloc(sizeof(char) * line_length);
      char *line_ptr = current_line->data;
      for (int i = 0; i < indentation; i++) {
        *line_ptr = ' ';
        line_ptr++;
      }
      memcpy(line_ptr, "obj1.", sizeof(char) * 5);
      line_ptr += 5;
      APPEND_TO_LINE(&line_ptr, current_field->data->name, field_name_length);
      memcpy(line_ptr, " == obj2. ", sizeof(char) * 9);
      line_ptr += 9;
      APPEND_TO_LINE(&line_ptr, current_field->data->name, field_name_length);
      if (!is_last_field) {
        memcpy(line_ptr, " &&", sizeof(char) * 3);
        line_ptr += 3;
      }
      line_ptr = "\0";
    }
    current_field = current_field->next;
  }

  current_line = next_line(current_line);
  current_line->data = "}";
}

char *create_field_line(const struct Field_List *field) {
  char *field_name = field->data->name;
  char *field_type = data_type_to_typescript_type(field->data->data_type);

  const int field_name_length = strlen(field_name);
  const int field_type_length = strlen(field_type);
  // <indentation><field_name>: <field_type>;\0
  const int field_line_length =
      indentation + field_name_length + 2 + field_type_length + 2;

  char *field_line = malloc(sizeof(*field_line) * field_line_length);
  char *field_ptr = field_line;
  for (int i = 0; i < indentation; i++) {
    *field_ptr = ' ';
    field_ptr++;
  }
  APPEND_TO_LINE(&field_ptr, field_name, field_name_length);
  memcpy(field_ptr, ": ", sizeof(char) * 2);
  field_ptr += sizeof(char) * 2;
  APPEND_TO_LINE(&field_ptr, field_type, field_type_length);
  *field_ptr = ';';
  field_ptr++;
  *field_ptr = '\0';

  return field_line;
}

struct Transpiled_Line *
transpile_typescript(const struct Class_Info *class_info) {
  struct Transpiled_Line *first_line = next_line(NULL);
  struct Transpiled_Line *current_line = first_line;

  current_line->data = create_type_declaration_line(class_info->name);
  current_line = next_line(current_line);

  // add fields
  struct Field_List *current_field = class_info->fields;
  while (current_field != NULL) {
    current_line->data = create_field_line(current_field);
    current_line = next_line(current_line);
    current_field = current_field->next;

    // Cleanup extra line if we've done every field
    if (current_field == NULL) {
      current_line = current_line->prev;
      free(current_line->next);
      current_line->next = NULL;
    }
  }

  // closing brance
  current_line = next_line(current_line);
  current_line->data = "}";
  current_line = next_line(current_line);

  // equality function
  if (class_info->equality == EQUAL_BY_VALUE) {
    create_equality_function(&current_line, class_info);
  }

  return first_line;
}
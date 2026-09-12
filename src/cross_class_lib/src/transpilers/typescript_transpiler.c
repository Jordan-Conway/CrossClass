#include "../../includes/transpilers/typescript_transpiler.h"
#include "class_info.h"
#include "tokens.h"
#include "transpilers/transpiler.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// This will be configurable at some point
const int indentation = 4;

static const char *export_type_string = "export type ";
static const int export_type_length = 12;
static const char *post_type_name_suffix_string = " {";
static const int post_type_name_suffix_length = 2;

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
  default:
    // TODO: Replace with actual type at some point
    printf("Encountered unknown type %d\n", type);
    return "";
  }
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
  strncpy(field_ptr, field_name, field_name_length);
  field_ptr += field_name_length;
  memcpy(field_ptr, ": ", sizeof(char) * 2);
  field_ptr += sizeof(char) * 2;
  strncpy(field_ptr, field_type, field_type_length);
  field_ptr += field_type_length;
  *field_ptr = ';';
  field_ptr++;
  *field_ptr = '\0';

  return field_line;
}

struct Transpiled_Line *
transpile_typescript(const struct Class_Info *class_info) {
  struct Transpiled_Line *first_line = next_line(NULL);
  struct Transpiled_Line *current_line = first_line;

  // export type <type_name> {
  int type_name_length = strlen(class_info->name);
  int type_line_length =
      type_name_length + export_type_length + post_type_name_suffix_length + 1;
  current_line->data = malloc(sizeof(char) * type_line_length);
  strncpy(current_line->data, export_type_string, export_type_length);
  strncpy(current_line->data + export_type_length, class_info->name,
          type_name_length);
  strncpy(current_line->data + export_type_length + type_name_length,
          post_type_name_suffix_string, post_type_name_suffix_length);
  current_line->data[type_line_length] = '\0';
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

  return first_line;
}
#include "../includes/data_parser.h"

#include "../includes/parsers/class_data_parser.h"
#include "../includes/tokens.h"
#include "../includes/version.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>

static struct Data_Parser_Result *create_default_result() {
  struct Data_Parser_Result *result =
      (struct Data_Parser_Result *)malloc(sizeof(struct Data_Parser_Result));

  result->is_error = false;
  result->result = NULL;
  result->error_message = NULL;

  return result;
}

struct Version *ensure_version(const struct Line_Data_Node *line) {
  if (strcmp("version", line->data->left) != 0) {
    printf("Expected to find version, instead found %s\n", line->data->left);
    return NULL;
  }
  char *version_string = line->data->right;

  int parts[3] = {0, 0, 0};
  int current_part = 0;
  bool part_empty = true;
  int char_index = 0;
  while (version_string[char_index] != '\0'){
    if (version_string[char_index] == '.'){
      if (part_empty){
        printf("Malformed version found. Part of the version is empty, "
           "instead found %s\n",
           version_string);
        return NULL;
      }
      current_part += 1;
      if (current_part >= 3){
        printf("Malformed version found. Version should be formatted as x.x.x, "
           "instead found %s\n",
           version_string);
        return NULL;
      };
      part_empty = true;
    }
    else if (isdigit(version_string[char_index]) == 0){
      printf("Malformed version found. Version should not contain non-numeric "
           "characters as digits, instead found %s\n",
           version_string);
      return NULL;
    }
    else if (part_empty){
      long int outcome = strtol(&version_string[char_index], NULL, 10);
      if(outcome > INT_MAX || outcome < 0){
        parts[current_part] = INT_MAX;
      } else{
        parts[current_part] = outcome;
      }
      part_empty = false;
    };
    char_index++;
  }
  if(current_part != 2 || part_empty){
    printf("Malformed version found. Version should be formatted as x.x.x, "
           "instead found %s\n",
           version_string);
    return NULL;
  }

  struct Version *version = malloc(sizeof(typeof(*version)));
  version->major = parts[0];
  version->minor = parts[1];
  version->patch = parts[2];

  return version;
}

enum Object_Type get_object_type(const struct Line_Data_Node *line) {
  if (strcmp(line->data->left, "type") != 0) {
    printf("Expect type, instead found %s\n", line->data->left);
    return OBJECT_TYPE_NONE;
  }

  if (strcmp(line->data->right, "class") == 0) {
    return OBJECT_TYPE_CLASS;
  }

  printf("Expected supported type, instead found %s\n", line->data->right);
  return OBJECT_TYPE_NONE;
}

struct Data_Parser_Result *
parse_line_data(struct Line_Data_Node *line_data_list) {
  struct Data_Parser_Result *result = create_default_result();

  struct Version *version = ensure_version(line_data_list);
  if (!version) {
    result->is_error = true;
    result->error_message = "Version either missing or not found";
    goto failure;
  }
  line_data_list = line_data_list->next;

  enum Object_Type type = get_object_type(line_data_list);
  if (type == OBJECT_TYPE_NONE) {
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
  } else {
    goto success;
  }

failure:
  free(result->result);
  result->result = NULL;
success:
  free(version);
  return result;
}
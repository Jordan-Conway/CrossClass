#include "../includes/transpilers/c_sharp_transpiler.h"
#include "../includes/class_info.h"
#include "../includes/tokens.h"
#include "transpilers/transpiler.h"
#include <stdlib.h>
#include <string.h>

const int max_line_length_without_class_name = 17;

struct Lines *default_line_list_node() {
  struct Lines *line_list_node = malloc(sizeof(typeof(*line_list_node)));
  line_list_node->data = NULL;
  line_list_node->prev = NULL;
  line_list_node->next = NULL;

  return line_list_node;
}

struct Lines *get_first_line(struct Lines *line_list) {
  while (line_list->prev != NULL) {
    line_list = line_list->prev;
  }

  return line_list;
}

char *create_class_name_line(const char *name,
                             const enum Visibility visibilty) {
  const int name_length = strlen(name);
  char *name_line =
      malloc(sizeof(char) * (max_line_length_without_class_name + name_length));
  char *current_pos = name_line;

  switch (visibilty) {
  case VISIBILITY_PRIVATE:
    strncpy(current_pos, "private", 7);
    current_pos += 7;
    break;
  case VISIBILITY_NOT_SET:
  case VISIBILITY_INTERNAL:
    strncpy(name_line, "internal", 8);
    current_pos += 8;
    break;
  case VISIBILITY_PUBLIC:
    strncpy(current_pos, "public", 6);
    current_pos += 6;
    break;
  }

  strncpy(current_pos, " ", 1);
  current_pos += 1;

  strncpy(current_pos, "class", 5);
  current_pos += 5;

  strncpy(current_pos, " ", 1);
  current_pos += 1;

  strncpy(current_pos, name, name_length);
  current_pos += name_length;
  strncpy(current_pos, " {\0", 3);

  return name_line;
}

struct TranspilerResult *
transpile_c_sharp(const struct Class_Info *class_info,
                  const struct TranspilerConfig *config) {
  struct TranspilerResult *result = malloc(sizeof(typeof(*result)));

  struct Lines *usings = default_line_list_node();
  struct Lines *class_lines = default_line_list_node();

  class_lines->data =
      create_class_name_line(class_info->name, class_info->visibility);

  usings->next = get_first_line(class_lines);
  result->file_data = get_first_line(usings);
  result->success = true;

  return result;
}
#ifndef TRANSPILER
#define TRANSPILER

#include "../linked_list.h"
#include <stdbool.h>

LIST_NODE(Lines, char);

struct TranspilerConfig {
  char *output_file;
};

struct TranspilerResult {
  bool success;
  char *error_message;
  struct Lines *file_data;
};

#endif
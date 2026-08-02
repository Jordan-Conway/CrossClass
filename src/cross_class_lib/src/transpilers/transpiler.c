#include "../includes/transpilers/transpiler.h"
#include <stdio.h>

bool write_result_to_file(const struct Lines *file_data,
                          const struct TranspilerConfig *config) {
  FILE *output_file = fopen(config->output_file, "w");

  if (output_file == NULL) {
    return false;
  }

  while (file_data != NULL) {
    if (file_data->data != NULL) {
      fprintf(output_file, "%s\n", file_data->data);
    }
    file_data = file_data->next;
  }

  fclose(output_file);
  return true;
}
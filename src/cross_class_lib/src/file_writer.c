#include "../includes/file_writer.h"
#include <stdio.h>
#include <stdlib.h>

void write_to_file(const struct Transpiled_Line *line, const char *file_path) {
  FILE *file = fopen(file_path, "w");

  if (file == NULL) {
    printf("Failed to create file %s\n", file_path);
    exit(1);
  }

  while (line != NULL) {
    if (line->data == NULL) {
      fprintf(file, "\n");
    } else {
      fprintf(file, "%s\n", line->data);
    }
    line = line->next;
  }

  fclose(file);
}
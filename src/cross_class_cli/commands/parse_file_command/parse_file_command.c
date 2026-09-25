#include "./parse_file_command.h"
#include "../command.h"
#include "ccx_line_data.h"
#include "ccx_reader.h"
#include "data_parser.h"
#include "file_writer.h"
#include "transpilers/transpiler.h"
#include "transpilers/typescript_transpiler.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Command_Result parse_file_command(int argc, char *argv[]) {
  if (argc != 3) {
    printf("Usage:\n");
    printf("cross_class_cli <transpiler> <input-file> <output-file>\n");
    exit(1);
  }

  char *transpiler = argv[0];
  char *input_file = argv[1];
  char *output_file = argv[2];

  struct Command_Result result = {.status = COMMAND_RESULT_NOT_SET,
                                  .message = ""};

  FILE *fptr = fopen(input_file, "r");

  if (fptr == NULL) {
    result.status = COMMAND_RESULT_FAILURE;
    result.message = "Failed to open file";
    exit(1);
  }

  struct Line_Data_Node *line_list = read_ccd_file(fptr);
  fclose(fptr);

  struct Data_Parser_Result *parse_result = parse_line_data(line_list);

  if (parse_result->error_message) {
    printf("Error message %s\n", parse_result->error_message);
  } else {
    printf("Parsed successfully\n");
  }

  struct Transpiled_Line *(*transpiler_command_ptr)(
      const struct Class_Info *class_info) = NULL;

  if (strcmp(transpiler, "ts") == 0) {
    transpiler_command_ptr = transpile_typescript;
  }

  if (transpiler_command_ptr == NULL) {
    printf("%s is not recognised as a valid transpiler\n", transpiler);
  } else {
    struct Transpiled_Line *transpiled_lines =
        transpiler_command_ptr(parse_result->result);
    write_to_file(transpiled_lines, output_file);
  }

  delete_list(line_list);
  free(parse_result);

  result.status = COMMAND_RESULT_SUCCESS;
  result.message = "Ok";

  return result;
}
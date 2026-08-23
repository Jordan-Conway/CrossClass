#include "./parse_file_command.h"
#include "../command.h"
#include "ccx_line_data.h"
#include "ccx_reader.h"
#include "data_parser.h"
#include <stdio.h>
#include <stdlib.h>

struct Command_Result parse_file_command(int, char *argv[]) {
  struct Command_Result result = {.status = COMMAND_RESULT_NOT_SET,
                                  .message = ""};

  FILE *fptr = fopen(argv[0], "r");

  if (fptr == NULL) {
    result.status = COMMAND_RESULT_FAILURE;
    result.message = "Failed to open file";
    exit(1);
  }

  struct Line_Data_Node *line_list = read_ccd_file(fptr);
  struct Data_Parser_Result *parse_result = parse_line_data(line_list);

  if (parse_result->error_message) {
    printf("Error message %s\n", parse_result->error_message);
  } else {
    printf("Parsed successfully\n");
  }

  delete_list(line_list);
  free(parse_result);
  fclose(fptr);

  result.status = COMMAND_RESULT_SUCCESS;
  result.message = "Ok";

  return result;
}
#include "./parse_file_command.h"
#include "../../DataParser/data_parser.h"
#include "../../data_reader.h"
#include "../../line_data_list.h"
#include "Commands/command.h"
#include <stdio.h>
#include <stdlib.h>

bool validate_parse_command_args(int argc, char* argv[]) {
    // TOOD validate args
    return true;
}

enum command_result parse_file_command(int argc, char* argv[]) {
    FILE *fptr = fopen(argv[1], "r");

    struct Line_Data_Node* line_list = read_ccd_file(fptr);
    struct Data_Parser_Result* parse_result = parse_line_data(line_list);

    printf("Parsed successfully: %d\n", !parse_result->is_error);
    printf("Error message %s\n", parse_result->error_message == NULL ? "" : parse_result->error_message);

    delete_list(line_list);
    free(parse_result);
    fclose(fptr);

    return COMMAND_RESULT_SUCCESS;
}
#include "./data_reader.h"
#include "./line_data_list.h"
#include "./DataParser/data_parser_result.h"
#include "./DataParser/data_parser.h"
#include <stdio.h>
#include <stdlib.h>

// DEVELOPMENT BEHAVIOUR - Print the .ccd file indicated by argv
int main(int argc, char* argv[]) {
    printf("%d\n", argc);
    
    if(argc != 2)
    {
        return 0;
    }

    FILE *fptr = fopen(argv[1], "r");

    struct Line_Data_Node* line_list = read_ccd_file(fptr);
    struct Data_Parser_Result* parse_result = parse_line_data(line_list);

    printf("Parsed successfully: %d\n", !parse_result->is_error);
    printf("Error message %s\n", parse_result->error_message == NULL ? "" : parse_result->error_message);

    delete_list(line_list);
    free(parse_result);
    fclose(fptr);

    return 0;
}
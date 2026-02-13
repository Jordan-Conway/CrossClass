#include "./data_parser_result.h"

#include <stdlib.h>

void delete_data_parser_result(struct Data_Parser_Result* result) {
    free(result->result);
    free(result->error_message);
    free(result);
}
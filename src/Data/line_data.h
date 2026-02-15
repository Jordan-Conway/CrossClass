#ifndef LINE_DATA
#define LINE_DATA

#include <stdbool.h>
#include "./Tokens/tokens.h"

struct Line_Data {
    int indentation;
    char* left;
    char* right;
};
 
// Compares two Line_Data structs for equality based on value
bool line_data_equality(const struct Line_Data *a, const struct Line_Data *b);

#endif



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
bool Line_Data_Eq(const struct Line_Data *a, const struct Line_Data *b);

#endif



#ifndef LINE_DATA
#define LINE_DATA

#include "./Tokens/tokens.h"

struct Line_Data {
    int indentation;
    char* left;
    char* right;
};

#endif
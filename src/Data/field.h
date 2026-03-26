#ifndef FIELD
#define FIELD

#include <stdbool.h>
#include "./Tokens/store_type.h"
#include "./Tokens/data_type.h"
#include "./Tokens/visability.h"

struct Field {
    enum DataType data_type;
    enum Visability visability;
    enum StoreType store_type;
    char* name;
    int name_length;
    bool isSigned;
    bool isConstant;
};

#endif
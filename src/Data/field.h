#include "./Tokens/store_type.h"
#include "./Tokens/data_type.h"
#include "./Tokens/visability.h"

struct Field {
    DataType data_type;
    Visability visability;
    StoreType store_type;
    char* name;
    int name_length;
    bool isSigned;
    bool isConstant;
};
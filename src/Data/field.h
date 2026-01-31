#include "./Tokens/store_type.h"
#include "./Tokens/type.h"
#include "./Tokens/visability.h"

struct Field {
    Type data_type;
    Visability visability;
    StoreType store_type;
    char* name;
    int name_length;
    bool isSigned;
    bool isConstant;
};
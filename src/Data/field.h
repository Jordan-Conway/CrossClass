#include <stdbool.h>
#include "./Tokens/store_type.h"
#include "./Tokens/type.h"
#include "./Tokens/visability.h"

struct Field {
    enum Type data_type;
    enum Visability visability;
    enum StoreType store_type;
    char* name;
    int name_length;
    bool isSigned;
    bool isConstant;
};
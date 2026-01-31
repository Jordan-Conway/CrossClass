#include "./field.h"
#include "./Tokens/equality_type.h"
#include "./Tokens/store_type.h"
#include "./Tokens/data_type.h"
#include "./Tokens/visability.h"

struct Equality {
    DataType type;
    char* excluded_fields;
    int num_excluded_fields;
};

struct Class {
    Visability visability;
    StoreType store_type;
    EqualityType equality;
    Field* fields;
    int num_fields;
    char* name;
};
#include "./field.h"
#include "./Tokens/equality_type.h"
#include "./Tokens/store_type.h"
#include "./Tokens/type.h"
#include "./Tokens/visability.h"

struct Equality {
    EqualityType type;
    char* (*excluded_fields)[];
};

struct ClassInfo {
    Visability visability;
    StoreType store_type;
    char* name;
    Equality equality;
    Field (*fields)[];
};
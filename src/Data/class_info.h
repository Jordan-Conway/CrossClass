#include "./field.h"
#include "./Tokens/equality_type.h"
#include "./Tokens/store_type.h"
#include "./Tokens/type.h"
#include "./Tokens/visability.h"

struct Equality {
    enum EqualityType type;
    char* (*excluded_fields)[];
};

struct ClassInfo {
    enum Visability visability;
    enum StoreType store_type;
    char* name;
    struct Equality equality;
    struct Field (*fields)[];
};
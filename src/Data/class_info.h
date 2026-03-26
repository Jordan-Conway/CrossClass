#ifndef CLASS_INFO
#define CLASS_INFO

#include "./field.h"
#include "./Tokens/equality_type.h"
#include "./Tokens/store_type.h"
#include "./Tokens/data_type.h"
#include "./Tokens/visability.h"

// Defines how equality is checked for objects
struct Equality {
    enum EqualityType type;
    char* (*excluded_fields)[]; // Fields to exclude from comparison
};

struct Class_Info {
    enum Visability visability;
    enum StoreType store_type;
    char* name;
    struct Equality equality;
    struct Field (*fields)[];
};

#endif
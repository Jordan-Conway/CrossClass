#ifndef CLASS_INFO
#define CLASS_INFO

#include "./field.h"
#include "./Tokens/equality_type.h"
#include "./Tokens/store_type.h"
#include "./Tokens/data_type.h"
#include "./Tokens/visability.h"

// Extends how equality is checked for classes
struct Equality {
    enum EqualityType type; //How are we comparing
    char* (*excluded_fields)[]; //What gets ignored when comparing
};

// Defines what is stored about a class
struct Class_Info {
    enum Visability visability;
    enum StoreType store_type;
    char* name;
    struct Equality equality;
    struct Field (*fields)[];
};

#endif
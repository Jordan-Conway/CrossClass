#ifndef TOKEN_TYPE
#define TOKEN_TYPE

enum Type {
    CHAR,
    STRING,

    INT8, 
    INT16,
    INT32, 
    INT64,
    INT128,

    FLOAT,
    DOUBLE,
    LONG_DOUBLE,

    BOOL,

    VOID,

    TIME,
    DATE,
    DATETIME,
    
    SELF, // Refers to the item being defined by the file
    DEFINED // Refers to an item defined in another file
};

#endif
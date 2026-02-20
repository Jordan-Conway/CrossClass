#ifndef TOKEN_TYPE
#define TOKEN_TYPE

enum DataType {
    DATATYPE_CHAR,
    DATATYPE_STRING,

    DATATYPE_INT8, 
    DATATYPE_INT16,
    DATATYPE_INT32, 
    DATATYPE_INT64,
    DATATYPE_INT128,

    DATATYPE_FLOAT,
    DATATYPE_DOUBLE,
    DATATYPE_LONG_DOUBLE,

    DATATYPE_BOOL,

    DATATYPE_VOID,

    DATATYPE_TIME,
    DATATYPE_DATE,
    DATATYPE_DATETIME,
    
    DATATYPE_SELF, // Refers to the item being defined by the file
    DATATYPE_DEFINED, // Refers to an item defined in another file

    DATATYPE_NOT_SET
};

#endif
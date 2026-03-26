#ifndef TOKEN_TYPE
#define TOKEN_TYPE

// Defines the valid types of data a field can store
enum DataType {
    DATA_DATA_CHAR,
    DATA_STRING,

    DATA_INT8, 
    DATA_INT16,
    DATA_INT32, 
    DATA_INT64,
    DATA_INT128,

    DATA_FLOAT,
    DATA_DOUBLE,
    DATA_LONG_DOUBLE,

    DATA_BOOL,

    DATA_VOID,

    DATA_TIME,
    DATA_DATE,
    DATA_DATETIME,

    DATA_SELF, // Refers to the item being defined by the file
    DATA_DEFINED // Refers to an item defined in another file
};

#endif
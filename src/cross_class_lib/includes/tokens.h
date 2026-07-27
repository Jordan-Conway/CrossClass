#ifndef TOKENS
#define TOKENS

// Defines the valid types of data a field can store
enum DataType {
  DATA_CHAR,
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

  DATA_SELF,    // Refers to the item being defined by the file
  DATA_DEFINED, // Refers to an item defined in another file

  DATA_NOT_SET
};

enum DataType data_type_from_str(char *str);

// Defines how an object should be implement equality
enum EqualityType { EQUAL_BY_VALUE, EQUAL_BY_REFERENCE, EQUAL_NOT_SET };

enum EqualityType equality_type_from_str(char *str);

enum Object_Type {
  OBJECT_TYPE_CLASS,
  OBJECT_TYPE_NONE,
};

// Defines how a field should be stored
enum StoreType {
  STORETYPE_STORE_BY_VALUE,
  STORETYPE_STORE_BY_REFERENCE,
  STORETYPE_NOT_SET
};

// Defines the visibility of an object or detail of an object
enum Visibility {
  VISIBILITY_PUBLIC,
  VISIBILITY_PRIVATE,
  VISIBILITY_INTERNAL,
  VISIBILITY_NOT_SET
};

enum Visibility visibility_from_str(char *str);

enum Token_Type {
  TOKENTYPE_DATA_TYPE_TOKEN,
  TOKENTYPE_EQUALITY_TYPE_TOKEN,
  TOKENTYPE_STORE_TYPE_TOKEN,
  TOKENTYPE_VISIBILITY_TOKEN
};

union Token {
  enum EqualityType equality_type;
  enum StoreType store_type;
  enum DataType data_type;
  enum Visibility visibility;
};

#endif
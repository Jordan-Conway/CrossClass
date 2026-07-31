#include "../includes/tokens.h"
#include <string.h>

#define match(value, matched_value, result)                                    \
  if (strcmp(value, matched_value) == 0) {                                     \
    return result;                                                             \
  }

enum DataType data_type_from_str(char *str) {
  match(str, "char", DATA_CHAR);
  match(str, "string", DATA_STRING);

  match(str, "i8", DATA_INT8);
  match(str, "i16", DATA_INT16);
  match(str, "i32", DATA_INT32);
  match(str, "i64", DATA_INT64);
  match(str, "i128", DATA_INT128);

  match(str, "float", DATA_FLOAT);
  match(str, "double", DATA_DOUBLE);
  match(str, "long double", DATA_LONG_DOUBLE);

  match(str, "bool", DATA_BOOL);

  match(str, "void", DATA_VOID);

  match(str, "time", DATA_TIME);
  match(str, "date", DATA_DATE);
  match(str, "datetime", DATA_DATETIME);

  match(str, "self", DATA_SELF);
  match(str, "defined", DATA_DEFINED);

  return DATA_NOT_SET;
}

enum EqualityType equality_type_from_str(char *str) {
  match(str, "value", EQUAL_BY_VALUE);
  match(str, "ref", EQUAL_BY_REFERENCE);

  return EQUAL_NOT_SET;
}

enum StoreType store_type_from_str(char *str) {
  match(str, "value", STORETYPE_STORE_BY_VALUE);
  match(str, "ref", STORETYPE_STORE_BY_REFERENCE);

  return STORETYPE_NOT_SET;
}

enum Visibility visibility_from_str(char *str) {
  match(str, "public", VISIBILITY_PUBLIC);
  match(str, "private", VISIBILITY_PRIVATE);
  match(str, "internal", VISIBILITY_INTERNAL);

  return VISIBILITY_NOT_SET;
}
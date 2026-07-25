#ifndef FIELD
#define FIELD

#include "./tokens.h"
#include <stdbool.h>

struct Field {
  enum DataType data_type;
  enum Visibility visibility;
  enum StoreType store_type;
  char *name;
  int name_length;
  bool isSigned;
  bool isConstant;
};

#endif
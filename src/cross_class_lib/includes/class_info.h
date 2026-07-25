#ifndef CLASS_INFO
#define CLASS_INFO

#include "./field.h"
#include "./tokens.h"

// Defines how equality is checked for objects
struct Equality {
  enum EqualityType type;
  char *(*excluded_fields)[]; // Fields to exclude from comparison
};

struct Class_Info {
  enum Visibility visibility;
  enum StoreType store_type;
  char *name;
  struct Equality *equality;
  struct Field (*fields)[];
};

#endif
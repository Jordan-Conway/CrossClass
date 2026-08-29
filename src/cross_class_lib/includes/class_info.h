#ifndef CLASS_INFO
#define CLASS_INFO

#include "./field.h"
#include "./linked_list.h"
#include "./tokens.h"

LIST_NODE(Field_List, Field)

struct Class_Info {
  enum Visibility visibility;
  char *name;
  enum EqualityType equality;
  struct Field_List *fields;
};

#endif

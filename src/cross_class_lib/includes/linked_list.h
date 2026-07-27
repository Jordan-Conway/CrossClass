#ifndef LINKED_LIST
#define LINKED_LIST

#define LIST_NODE(t_name, t_type)                                              \
  struct t_name {                                                              \
    struct t_type *data;                                                       \
    struct t_name *prev;                                                       \
    struct t_name *next;                                                       \
  };

#endif
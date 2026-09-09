#ifndef VERSION
#define VERSION

#include "./linked_list.h"
#include <stdbool.h>

struct Version {
  int major;
  int minor;
  int patch;
};

LIST_NODE(Version_List, Version)

struct Version get_current_version();

bool ensure_version_supported(const struct Version *version);

char *version_to_str(const struct Version *version);

#endif
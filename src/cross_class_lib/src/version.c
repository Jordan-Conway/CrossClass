#include "../includes/version.h"

#include <stdbool.h>
#include <stdlib.h>

#include <stdio.h>

const struct Version CURRENT_VERSION = {
    .major = 0,
    .minor = 0,
    .patch = 0,
};

struct Version get_current_version() { return CURRENT_VERSION; }

// Auxiliary function to minimize space
void add_supported_version(struct Version_List **tail, int major, int minor,
                           int patch) {
  (*tail)->next = malloc(sizeof(typeof(*((*tail)->next))));
  struct Version_List *new_version = (*tail)->next;
  new_version->data = malloc(sizeof(typeof((*new_version->data))));
  new_version->data->major = major;
  new_version->data->minor = minor;
  new_version->data->patch = patch;
  new_version->next = NULL;
  new_version->prev = *tail;
  *tail = new_version;
}

// Just list out all accepted versions, at most 1 per major version
struct Version_List *get_supported_versions() {
  struct Version supported_version_data = get_current_version();

  struct Version_List *version_list = malloc(sizeof(typeof(*version_list)));
  version_list->data = &supported_version_data;
  version_list->next = NULL;
  version_list->prev = NULL;

  add_supported_version(&version_list, 1, 0,
                        0); // Initial supporting version
  return version_list;
}

bool ensure_version_supported(const struct Version *version) {
  // DEVELOPMENT BYPASS - WILL BE REMOVED ONCE STABLE VERSIONS ARE HERE
  if (version->major == 0) {
    return true;
  }

  struct Version_List *supported_versions = get_supported_versions();

  if (supported_versions == NULL) {
    return false; // Error case/No versions are supported
  }

  // Walk the version list backwards
  bool valid = false;
  bool finished = false;
  while (!finished) {
    if (version->major != supported_versions->data->major) {
      if (supported_versions->prev == NULL) {
        finished = true;
      } else {
        supported_versions = supported_versions->prev;
      }
      continue;
    }

    // Major version matches, so ensure CrossClass version > file version
    finished = true;
    if (version->minor < supported_versions->data->minor) {
      valid = true;
    } else if (version->minor > supported_versions->data->minor) {
      valid = false;
    } else {
      valid = true;
    }
  }

  // Finish winding back
  while (supported_versions->prev != NULL) {
    supported_versions = supported_versions->prev;
  }
  // Free up memory
  while (supported_versions->next != NULL) {
    supported_versions = supported_versions->next;
    free(supported_versions->prev);
  }
  free(supported_versions);

  return valid;
}

int num_digits(int value) {
  int digits = 0;

  if (value == 0) {
    return 1;
  }

  while (value != 0) {
    digits++;
    value /= 10;
  }

  return digits;
}

char *version_to_str(const struct Version *version) {
  if (version == NULL) {
    return NULL;
  }

  int major_length = num_digits(version->major);
  int minor_length = num_digits(version->minor);
  int patch_length = num_digits(version->patch);

  // Extra 3 for two dots and null terminator
  int total_length = major_length + minor_length + patch_length + 3;

  char *result = malloc(sizeof(typeof(*result)) * total_length);
  sprintf(result, "%d.%d.%d", version->major, version->minor, version->patch);

  return result;
}
#include "./version.h"

const struct Version CURRENT_VERSION = {
    .major = 0,
    .minor = 0,
    .patch = 0,
};

struct Version get_current_version() {
    return CURRENT_VERSION;
}
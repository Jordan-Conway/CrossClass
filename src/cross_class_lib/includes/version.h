#ifndef VERSION
#define VERSION

struct Version {
    int major;
    int minor;
    int patch;
};

struct Version get_current_version();

#endif
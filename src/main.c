#include "./Data/class_info.h"
#include <stdio.h>

int main() {
    struct ClassInfo class_info;
    class_info.name = "My Name\n";

    printf("%s", class_info.name);

    return 0;
}
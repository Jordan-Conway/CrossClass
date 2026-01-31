#include "./class_reader.h"

#include "../Data/class.h"
#include <stdio.h>

Class read_class_from_file(char* path) {
    FILE* file = fopen(path, "r");
    
    if (file == NULL) {
        return NULL;
    }

    delete file;
}
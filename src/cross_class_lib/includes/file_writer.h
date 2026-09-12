#ifndef CC_LIB_FILE_WRITER
#define CC_LIB_FILE_WRITER

#include "./transpilers/transpiler.h"

void write_to_file(const struct Transpiled_Line *line, const char *file_path);

#endif
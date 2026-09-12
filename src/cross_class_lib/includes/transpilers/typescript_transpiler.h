#ifndef CC_LIB_TYPESCRIPT_TRANSPILER
#define CC_LIB_T

#include "class_info.h"
#include "transpiler.h"

struct Transpiled_Line *
transpile_typescript(const struct Class_Info *class_info);

#endif
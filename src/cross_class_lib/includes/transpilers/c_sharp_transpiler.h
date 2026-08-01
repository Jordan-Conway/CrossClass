#ifndef C_SHARP_TRANSPILER
#define C_SHARP_TRANSPILER

#include "class_info.h"
#include "transpilers/transpiler.h"

struct TranspilerResult *
transpile_c_sharp(const struct Class_Info *class_info,
                  const struct TranspilerConfig *config);

#endif
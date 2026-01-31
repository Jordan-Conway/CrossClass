#include "../Data/Tokens/data_type.h"
#include "../Data/Tokens/equality_type.h"
#include "../Data/Tokens/store_type.h"
#include "../Data/Tokens/visability.h"

enum TokenType {
    DATA_TYPE,
    EQUALITY_TYPE,
    STORE_TYPE,
    VISABILTY,
};

struct TokenEntry {
    TokenType type;
    union {
        DataType data_type;
        EqualityType equality_type;
        StoreType store_type;
        Visability visability;
    } value;
};


#include "./equality_type.h"
#include "./store_type.h"
#include "./data_type.h"
#include "./visability.h"

enum Token_Type{
    TOKENTYPE_DATA_TYPE_TOKEN,
    TOKENTYPE_EQUALITY_TYPE_TOKEN,
    TOKENTYPE_STORE_TYPE_TOKEN,
    TOKENTYPE_VISABILITY_TOKEN
};

union Token{
    enum EqualityType equality_type;
    enum StoreType store_type;
    enum DataType data_type;
    enum Visability visability;
};
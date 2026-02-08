#include "./equality_type.h"
#include "./store_type.h"
#include "./data_type.h"
#include "./visability.h"

union Token{
    enum EqualityType equality_type;
    enum StoreType store_type;
    enum DataType data_type;
    enum Visability visability;
};
#include "./equality_type.h"
#include "./store_type.h"
#include "./data_type.h"
#include "./visability.h"

// Defines a single attribute of a class
union Token{
    enum EqualityType equality_type;
    enum StoreType store_type;
    enum DataType data_type;
    enum Visability visability;
};
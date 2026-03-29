#ifndef TOKEN_STORETYPE
#define TOKEN_STORETYPE

// Defines how a field should be stored
enum StoreType {
    STORETYPE_STORE_BY_VALUE,
    STORETYPE_STORE_BY_REFERENCE,
    STORETYPE_NOT_SET
};

#endif
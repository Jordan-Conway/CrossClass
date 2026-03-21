#ifndef TOKEN_VISABILITY
#define TOKEN_VISABILITY

// Defines where a token can be accessed
enum Visability {
    VISABILITY_PUBLIC, // Accessible in all classes
    VISABILITY_PRIVATE, // Accessible only in the same class
    VISABILITY_INTERNAL  // Accessible only from the same assembly/file
};

#endif

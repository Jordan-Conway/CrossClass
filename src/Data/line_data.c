#include "./line_data.h"
#include <string.h> 
#include <stdlib.h> 

bool Line_Data_Eq(const struct Line_Data *a, const struct Line_Data *b) {
   
    if (a == b) {
        return true;
    }

    if (a == NULL || b == NULL) {
        return false;
    }

    if (a->indentation != b->indentation) {
        return false;
    }

    // Handle cases where strings might be NULL to avoid crashing
    if (a->left && b->left) {
        if (strcmp(a->left, b->left) != 0) return false;
    } else if (a->left != b->left) {
        return false;
    }

    if (a->right && b->right) {
        if (strcmp(a->right, b->right) != 0) return false;
    } else if (a->right != b->right) {
        return false;
    }

    return true;
}

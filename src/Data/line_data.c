#include "./line_data.h"
#include <string.h> 
#include <stdlib.h> 

// Compares two Line_Data structs for equality based on value
bool line_data_equality(const struct Line_Data *a, const struct Line_Data *b) {
   
    // Trivial cases
    if (a == b) {
        return true;
    }

    if (a == NULL || b == NULL) {
        return false;
    }

    // Guard clauses for non-trivial cases
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

// Frees up the memory claimed by Line_Data
void delete_data(struct Line_Data* data){
    if (data) {
        free(data->left);
        free(data->right);
    }
    free(data);
}
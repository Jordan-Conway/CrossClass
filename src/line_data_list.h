#include "./Data/line_data.h"

#include <stdbool.h>

struct Line_Data_Node {
    struct Line_Data* data;
    struct Line_Data_Node* prev;
    struct Line_Data_Node* next;
};

struct Line_Data_Node* create_line_data_list();

// Appends data to the end of the linked list
struct Line_Data_Node* append_line_data(struct Line_Data_Node*, struct Line_Data* data);

// Gets the head of the list
struct Line_Data_Node* get_head_of_line_data_list(struct Line_Data_Node *list);

// Deletes all entries in the list regardless of which is passed in
void delete_list(struct Line_Data_Node* list);

// Compares the data content of two nodes
bool Line_Data_Node_Eq(const struct Line_Data_Node* a, const struct Line_Data_Node* b);

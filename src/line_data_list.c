#include "./line_data_list.h"

#include <stdio.h>
#include <stdlib.h>

struct Line_Data_Node* create_line_data_list(){
    struct Line_Data_Node* node = (struct Line_Data_Node*)calloc(1, sizeof(struct Line_Data_Node));

    node->data = NULL;
    node->next = NULL;
    node->prev = NULL;

    return node;
}

struct Line_Data_Node* append_line_data(struct Line_Data_Node* list, struct Line_Data* data){
    struct Line_Data_Node* tail = create_line_data_list();

    tail->prev = list;
    tail->data = data;

    if (list != NULL){
        list->next = tail;
    }

    return tail;
} 

struct Line_Data_Node* get_head_of_line_data_list(struct Line_Data_Node *list){
    if(list == NULL){
        printf("Cannot get head of null list");
        exit(1);
    }

    while (list->prev != NULL) {
        list = list->prev;
    }

    return list;
}

void delete_list(struct Line_Data_Node* list){
    struct Line_Data_Node* current_tail = get_head_of_line_data_list(list);

    while (current_tail->next != NULL) {
        current_tail = current_tail->next;
    }

    while (current_tail != NULL) {
        free(current_tail->data->left);
        free(current_tail->data->right);
        free(current_tail->data);
        current_tail = current_tail->prev;

        if(current_tail != NULL){
            free(current_tail->next);
        }
    }
}
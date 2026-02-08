#include "./line_data_list.h"
#include "Data/line_data.h"

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
    struct Line_Data_Node* tail = list;

    while (tail && tail->next) {
        tail = tail->next;
    }

    struct Line_Data_Node* new_tail = create_line_data_list();

    new_tail->prev = tail;
    new_tail->data = data;

    if (list != NULL){
        tail->next = new_tail;
    }

    return new_tail;
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

void delete_data(struct Line_Data* data){
    if (data) {
        free(data->left);
        free(data->right);
    }
    free(data);
}

void delete_list(struct Line_Data_Node* list){
    struct Line_Data_Node* current_head = get_head_of_line_data_list(list);

    while (current_head->next != NULL) {
        delete_data(current_head->data);
        current_head = current_head->next;
        free(current_head->prev);
    }

    delete_data(current_head->data);
    free(current_head);
}
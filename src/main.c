#include "./data_reader.h"
#include "./line_data_list.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
    printf("%d\n", argc);
    
    if(argc != 2)
    {
        return 0;
    }

    FILE *fptr = fopen(argv[1], "r");

    struct Line_Data_Node* line_list = read_ccd_file(fptr);
    
    printf("No next? %d", line_list->next == NULL);
    while (line_list->next != NULL) {
        printf("Left: %s", line_list->data->left);
        printf("Right: %s", line_list->data->right);
        line_list = line_list->next;
    }
    
    line_list = get_head_of_line_data_list(line_list);
    delete_list(line_list);

    fclose(fptr);

    return 0;
}
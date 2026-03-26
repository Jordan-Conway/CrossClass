#include "./data_reader.h"

#include "./Data/line_data.h"
#include "./line_data_list.h"
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// TODO: Handle arbitrary line lengths
size_t MAX_LINE_LENGTH = 100;

// Simple error handler
void error_invalid_line(char* const reason_msg){
    printf("Line is invalid\n");
    printf("%s\n", reason_msg);
    exit(1);        
}

// Parse a single line (left to right)
struct Line_Data* parse_line(const char* line){
    /*
     * A line is one of:
     * - Whitespace (ignore)
     * - A comment (ignore)
     * - The start of a section (no right data)
     * - A detail (key [left]: value [right])
     * - An error (raise)
     */
    struct Line_Data* line_data = (struct Line_Data*)calloc(1, sizeof(struct Line_Data));
    line_data->left = (char*)calloc(MAX_LINE_LENGTH, sizeof(char));
    line_data->right = (char*)calloc(MAX_LINE_LENGTH,sizeof(char));
    line_data->indentation = 0;

    bool is_left = true;
    int index = 0; // index of the newest character
    
    // Parse character by character
    for(int i=0; i<MAX_LINE_LENGTH; i++)
    {
        char currentChar = *(line + i);

        // Handle the end of the line
        if(currentChar == '\n' || currentChar == '\0'){
            if(is_left){
                error_invalid_line("Found end of line without finding ':'");
            }
            if(index != -1){ // If right-side is not empty
                while(isspace(line_data->right[index])){ // Trim trailing whitespace
                    index--;
                }
            }
            index++;
            line_data->right[index] = '\0';
            break;
        }

        // Handle swaps between left and right
        if(currentChar == ':'){
            if(!is_left){
                error_invalid_line("Found ':' on right side of declaration");
            }
            if(index == -1){
                error_invalid_line("Left is empty");
            }
            is_left = false;
            while(isspace(line_data->left[index])){ // Trim trailing whitespace
                index--;
            }
            index++;
            line_data->left[index] = '\0';
            index = -1;
            continue;
        }

        // Handle indentation
        if(isspace(currentChar) && index == -1){
            if(is_left){
                line_data->indentation++;
            }
            continue;
        }

        // Store the character
        index++;
        if(is_left)
        {
            line_data->left[index] = tolower(currentChar);
        }
        else{
            line_data->right[index] = currentChar;
        }
    }

    return line_data;
}


// Parse a file (top to bottom)
struct Line_Data_Node* read_ccd_file(FILE *file) {
    char* current_line = (char *)calloc(MAX_LINE_LENGTH, sizeof(char));
    struct Line_Data_Node* line_data_list = NULL;

    long chars_read;
    int lines_read = 0;

    do{
        chars_read = getline(&current_line, &MAX_LINE_LENGTH, file);
        if (chars_read <= 0){
            if(lines_read == 0){
                goto empty_file;
            }
            lines_read++;
            continue;
        }
        lines_read++;

        // Skip empty lines
        if(chars_read < 2)
        {
            continue;
        }

        // Ignore comments
        if (*current_line == *(current_line+1) && *current_line == '/')
        {
            continue;
        }

        if (chars_read == MAX_LINE_LENGTH)
        {
            error_invalid_line("Line longer than max permitted");
        }

        // Last line of file won't have a new line
        if (*(current_line + chars_read -1) != '\n')
        {
            *(current_line + chars_read) = '\n';
        }
        
        line_data_list = append_line_data(line_data_list, parse_line(current_line));

    }while(chars_read != -1);
    goto success;

empty_file:
    // TODO print file name
    printf("File is empty");
    exit(1);

success:
    free(current_line);
    line_data_list = get_head_of_line_data_list(line_data_list);
    return line_data_list;
};
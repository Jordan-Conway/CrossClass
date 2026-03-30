#include "./data_reader.h"

#include "./Data/line_data.h"
#include "./line_data_list.h"
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// Simple error handler
void error_invalid_line(char* const reason_msg){
    printf("Line is invalid\n");
    printf("%s\n", reason_msg);
    exit(1);        
}

// Determine the length of a line by reading 32 character chunks
size_t get_line_length(FILE *file, size_t* left_length, size_t* right_length){
    int total_length = 0;
    int chunk_length = 0;
    char buffer[32];
    bool is_done = false;
    bool colon_seen = false;

    do{
        // Count number of characters
        do{
            buffer[chunk_length] = fgetc(file);       
            if(feof(file) || buffer[chunk_length] == '\n' || buffer[chunk_length] == '\0'){
                is_done = true;
            }
            if(buffer[chunk_length] == ':'){ // Test for colon (switch to counting right side)
                colon_seen = true;
            }
            chunk_length++;
        } while(chunk_length < 32 && !is_done && !colon_seen);

        // Put back onto the input stream
        for(int i = chunk_length - 1; i > -1; i--)
        {
            ungetc(buffer[i], file);
        }

        total_length += chunk_length;
        fseek(file, chunk_length, SEEK_CUR); // Make sure we don't read the same part repeatedly
        chunk_length = 0;

        // Switch to counting right side upon first colon
        if(colon_seen && *left_length == 0){
            *left_length = total_length;
            colon_seen = false;
        }
    } while(!is_done);

    *right_length = total_length - *left_length;
    fseek(file, -total_length, SEEK_CUR); // Roll back the file pointer for the parser
    return total_length;
}

// Parses the left side of a line. The result is stored in result. Moves line up to the first ':'. Return the amount of indentation
int parse_left(const char** line, char** result) {
    int nextIndex = 0;
    int indent = 0;

    while(**line != ':'){
        //Spaces before the first character are indentation
        while(**line == ' ' && nextIndex == 0){
            indent++;
            (*line)++;
        }

        char currentChar = **line;

        // Left side has to end with ':'
        if(currentChar == '\n' || currentChar == '\0') {
            error_invalid_line("Found end of left without finding :");
        }

        (*result)[nextIndex] = tolower(currentChar);
        nextIndex++;
        (*line)++;
    }

    // Trim trailing whitespace
    int currIndex = nextIndex -1;
    while(isspace((*result)[currIndex]))
    {
        currIndex--;
    }
    (*result)[currIndex+1] = '\0';

    return indent;
}

void parse_right(const char** line, char** result) {
    int nextIndex = 0;
    
    while (**line != '\n' && **line != '\0') {
        //Ignore spaces before the first character
        while(**line == ' ' && nextIndex == 0){
            (*line)++;
        }

        (*result)[nextIndex] = **line;
        nextIndex++;
        (*line)++;
    }

    // Trim trailing whitespace
    int currIndex = nextIndex -1;
    while(isspace((*result)[currIndex]))
    {
        currIndex--;
    }
    (*result)[currIndex+1] = '\0';
}

// Parse a single line (left to right)
struct Line_Data* parse_line(const char* line, const size_t LEFT_LENGTH, const size_t RIGHT_LENGTH){
    /*
     * A line is one of:
     * - Whitespace (ignore)
     * - A comment (ignore)
     * - The start of a section (no right data)
     * - A detail (key [left]: value [right])
     * - An error (raise)
     */
    struct Line_Data* line_data = (struct Line_Data*)calloc(1, sizeof(struct Line_Data));
    line_data->left = (char*)calloc(LEFT_LENGTH, sizeof(char));
    line_data->right = (char*)calloc(RIGHT_LENGTH,sizeof(char));

    line_data->indentation = parse_left(&line, &line_data->left);
    line++; //Line comes back from parse_left pointing at ':'

    parse_right(&line, &line_data->right);

    return line_data;
}


// Parse a file (top to bottom)
struct Line_Data_Node* read_ccd_file(FILE *file) {
    char* current_line = NULL;
    struct Line_Data_Node* line_data_list = NULL;

    long chars_read;
    int lines_read = 0;

    do{
        size_t left_length = 0, right_length = 0;
        size_t line_length = get_line_length(file, &left_length, &right_length);
        current_line = (char *)realloc(current_line, line_length * sizeof(char));
        chars_read = getline(&current_line, &line_length, file);
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

        // Last line of file won't have a new line
        if (*(current_line + chars_read -1) != '\n')
        {
            *(current_line + chars_read) = '\n';
        }

        if(line_length == 1){
            error_invalid_line("Left is empty");
        }
        
        line_data_list = append_line_data(line_data_list, parse_line(current_line, left_length, right_length));

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
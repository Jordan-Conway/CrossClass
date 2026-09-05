#include "../includes/ccx_reader.h"

#include "../includes/ccx_line_data.h"
#include <ctype.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

// Simple error handler
void error_invalid_line(const char *const reason_msg) {
  printf("Line is invalid\n");
  printf("%s\n", reason_msg);
  exit(1);
}

size_t get_length_of_part(const char *line, char delimeter) {
  size_t length = 0;
  int spaces_in_a_row = 0;

  while (*line != delimeter && *line != '\0') {
    if (*line == ' ') {
      spaces_in_a_row++;
      if (length != 0) {
        length++;
      }
    } else {
      spaces_in_a_row = 0;
      length++;
    }
    line++;
  }

  if (length == 0) {
    return 0;
  }

  return length - spaces_in_a_row;
}

// Determine the length of both parts of the line, excluding leading and
// trailing white space
void get_part_lengths(const char *line, size_t *left_length,
                      size_t *right_length) {
  *left_length = 0;
  *right_length = 0;

  if (*line == '\0') {
    return;
  }

  *left_length = get_length_of_part(line, ':');
  while (*line != ':') {
    if (*line == '\0' || *line == '\n') {
      return;
    }
    line++;
  }
  line++;
  *right_length = get_length_of_part(line, '\n');
}

// Parses the left side of a line. The result is stored in result. Moves line up
// to the first ':'. Return the amount of indentation
int parse_left(const char **line, char **result) {
  int nextIndex = 0;
  int indent = 0;

  while (**line != ':') {
    // Spaces before the first character are indentation
    while (**line == ' ' && nextIndex == 0) {
      indent++;
      (*line)++;
    }

    char currentChar = **line;

    // Left side has to end with ':'
    if (currentChar == '\n' || currentChar == '\0') {
      error_invalid_line("Found end of left without finding :");
    }

    (*result)[nextIndex] = tolower(currentChar);
    nextIndex++;
    (*line)++;
  }

  // Trim trailing whitespace
  int currIndex = nextIndex - 1;
  while (isspace((*result)[currIndex])) {
    currIndex--;
  }
  (*result)[currIndex + 1] = '\0';

  return indent;
}

void parse_right(const char **line, char **result) {
  int nextIndex = 0;

  while (**line != '\n' && **line != '\0') {
    // Ignore spaces before the first character
    while (**line == ' ' && nextIndex == 0) {
      (*line)++;
    }

    (*result)[nextIndex] = **line;
    nextIndex++;
    (*line)++;
  }

  // Trim trailing whitespace
  int currIndex = nextIndex - 1;
  while (currIndex > -1 && isspace((*result)[currIndex])) {
    currIndex--;
  }
  (*result)[currIndex + 1] = '\0';
}

// Parse a single line (left to right)
struct Line_Data *parse_line(const char *line, const size_t LEFT_LENGTH,
                             const size_t RIGHT_LENGTH) {
  /*
   * A line is one of:
   * - Whitespace (ignore)
   * - A comment (ignore)
   * - The start of a section (no right data)
   * - A detail (key [left]: value [right])
   * - An error (raise)
   */
  struct Line_Data *line_data =
      (struct Line_Data *)calloc(1, sizeof(struct Line_Data));
  line_data->left = (char *)calloc(LEFT_LENGTH, sizeof(char));
  line_data->right = (char *)calloc(RIGHT_LENGTH, sizeof(char));

  line_data->indentation = parse_left(&line, &line_data->left);
  line++; // Line comes back from parse_left pointing at ':'

  parse_right(&line, &line_data->right);

  return line_data;
}

char *read_line(FILE *file) {
  size_t capacity = 128;
  size_t length = 0;
  char *line = malloc(capacity);

  if (line == NULL) {
    return NULL;
  }

  int last_char;

  while ((last_char = fgetc(file)) != EOF && last_char != '\n') {
    if (length + 1 >= capacity) {
      capacity *= 2;

      char *temp = realloc(line, capacity);
      if (temp == NULL) {
        free(line);
        return NULL;
      }

      line = temp;
    }

    line[length++] = (char)last_char;
  }

  if (last_char == EOF && length == 0) {
    free(line);
    return NULL;
  }

  line[length] = '\0';
  return line;
}

// Parse a file (top to bottom)
struct Line_Data_Node *read_ccd_file(FILE *file) {
  char *current_line = NULL;
  struct Line_Data_Node *line_data_list = NULL;

  while ((current_line = read_line(file)) != NULL) {
    // Ignore comments
    if (*current_line == *(current_line + 1) && *current_line == '/') {
      continue;
    }

    size_t left_length;
    size_t right_length;
    get_part_lengths(current_line, &left_length, &right_length);

    // Skip empty lines
    if (left_length + right_length == 0) {
      continue;
    }

    // Right cannot have value if left is empty
    if (left_length == 0) {
      error_invalid_line("Left is empty");
    }

    line_data_list = append_line_data(
        line_data_list, parse_line(current_line, left_length, right_length));
  };
  goto success;

success:
  free(current_line);
  line_data_list = get_head_of_line_data_list(line_data_list);
  return line_data_list;
}

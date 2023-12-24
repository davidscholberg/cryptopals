#include <string.h>

#include "string_utils.h"

void concat_lines(const char* const multiline_str, char* const one_line_str) {
    const int multiline_str_size = strlen(multiline_str);
    int dest_i = 0;
    for (int src_i = 0; src_i < multiline_str_size; src_i++) {
        if (multiline_str[src_i] != '\n') {
            one_line_str[dest_i] = multiline_str[src_i];
            dest_i++;
        }
    }
}

int concat_lines_size(const char* const multiline_str) {
    const int total_str_size = strlen(multiline_str);
    int line_count = 0;
    for (int i = 0; i <= total_str_size; i++) {
        if (multiline_str[i] == '\n') line_count++;
    }
    return total_str_size - line_count;
}

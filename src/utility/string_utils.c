#include <stdlib.h>
#include <string.h>

#include "log.h"
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
    one_line_str[dest_i] = 0;
}

int concat_lines_size(const char* const multiline_str) {
    const int total_str_size = strlen(multiline_str);
    int line_count = 0;
    for (int i = 0; i <= total_str_size; i++) {
        if (multiline_str[i] == '\n') line_count++;
    }
    return total_str_size - line_count + 1;
}

char** split_string(const char* const multiline_str, int* const split_count) {
    *split_count = 1;
    int str_size = 0;
    while(multiline_str[str_size]) {
        if (multiline_str[str_size] == '\n' && multiline_str[str_size + 1])
            (*split_count)++;
        str_size++;
    }

    const int array_of_splits_size = (sizeof(char*) * *split_count);
    const int splits_strings_size = str_size + 1;
    const int total_bytes_needed = array_of_splits_size + splits_strings_size;

    void* byte_buffer = malloc(total_bytes_needed);
    if (!byte_buffer) {
        log_error("malloc failed");
        return 0;
    }

    char** splits = byte_buffer;
    char* splits_strings = (char*)byte_buffer + array_of_splits_size;

    int splits_i = 0;
    bool split_start = true;
    for (int i = 0; i < str_size; i++) {
        if (split_start) {
            splits[splits_i] = splits_strings + i;
            splits_i++;
            split_start = false;
        }

        if (multiline_str[i] != '\n') {
            splits_strings[i] = multiline_str[i];
        } else {
            splits_strings[i] = 0;
            split_start = true;
        }
    }
    splits_strings[str_size] = 0;

    return splits;
}

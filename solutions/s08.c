#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "analysis/repeating_blocks.h"
#include "codecs/decode_lines.h"
#include "codecs/hex.h"
#include "utility/files.h"

#define block_size 16

// Challenge 8: Detect which input string has been encrypted with AES ECB.
bool s08(char* const out_buffer, __attribute__((unused)) const int out_buffer_size) {
    int line_count = 0;
    char** lines = file_to_lines("s08_hex_string_array.txt", &line_count);
    if (!lines) {
        return false;
    }

    int* buffer_sizes = 0;
    unsigned char** buffers =
        decode_lines(lines, line_count, hex_to_bytes, hex_to_bytes_size_wrapper, &buffer_sizes);
    if (!buffers) {
        free(lines);
        return false;
    }

    int guessed_index = 0;
    for (int i = 0; i < line_count; i++) {
        if (repeating_blocks(buffers[i], buffer_sizes[i], block_size)) {
            guessed_index = i;
            break;
        }
    }

    strcpy(out_buffer, lines[guessed_index]);

    free(lines);
    free(buffers);

    return true;
}

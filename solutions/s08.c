#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "analysis/repeating_blocks.h"
#include "codecs/hex.h"
#include "resources/s08_string_array.h"

#define block_size 16

// Challenge 8: Detect which input string has been encrypted with AES ECB.
bool s08(char* const out_buffer, __attribute__((unused)) const int out_buffer_size) {
    int guessed_index = 0;
    for (int i = 0; i < s08_string_array_size; i++) {
        const int input_bytes_size = hex_to_bytes_size(strlen(s08_string_array[i]));
        unsigned char input_bytes[input_bytes_size];
        if (!hex_to_bytes(s08_string_array[i], input_bytes, input_bytes_size)) {
            return false;
        }

        if (repeating_blocks(input_bytes, input_bytes_size, block_size)) {
            guessed_index = i;
            break;
        }
    }

    strcpy(out_buffer, s08_string_array[guessed_index]);
    return true;
}

#include <stdbool.h>
#include <stdlib.h>

#include "ciphers/xor.h"
#include "codecs/decode_lines.h"
#include "codecs/hex.h"
#include "resources/resources.h"
#include "uncrypt/break_xor.h"
#include "utility/files.h"

// Challenge 4: Find the string in the input array that has been single-byte xored.
bool s04(char* const out_buffer, const int out_buffer_size) {
    status = false;

    int max_hex_strlen = 0;
    int current_strlen = 0;
    for (int i = 0; i < s04_hex_string_array_txt_size; i++) {
        if (s04_hex_string_array_txt[i] == '\n') {
            if (current_strlen > max_hex_strlen)
                max_hex_strlen = current_strlen;
            current_strlen = 0;
            continue;
        }
        current_strlen++;
    }
    int line_count = 0;
    char** lines = file_to_lines("s04_hex_string_array.txt", &line_count);
    if (!lines) {
        return false;
    }

    int* buffer_sizes = 0;
    unsigned char** buffers =
        decode_lines(lines, line_count, hex_to_bytes, hex_to_bytes_size_wrapper, &buffer_sizes);
    free(lines);
    if (!buffers) {
        return false;
    }

    float max_english_score = 0;
    unsigned char best_key_char = 0;
    int best_string_index = 0;
    for (int i = 0; i < line_count; i++) {
        float score;
        unsigned char key_char = 0;
        unsigned char result_buffer[buffer_sizes[i]];
        break_single_byte_xor(buffers[i], buffer_sizes[i], result_buffer, 0, 1, &key_char, &score);

        if (score > max_english_score) {
            max_english_score = score;
            best_key_char = key_char;
            best_string_index = i;
        }
    }

    if (buffer_sizes[best_string_index] + 1 > out_buffer_size) {
        free(buffers);
        return false;
    }

    xor_byte(
        buffers[best_string_index],
        buffer_sizes[best_string_index],
        best_key_char,
        (unsigned char*)out_buffer,
        0,
        1
    );
    out_buffer[buffer_sizes[best_string_index]] = 0;

    return true;
}

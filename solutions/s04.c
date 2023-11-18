#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "ciphers/xor.h"
#include "codecs/hex.h"
#include "resources/s04_string_array.h"
#include "uncrypt/break_xor.h"

// Challenge 4: Find the string in the input array that has been single-byte xored.
bool s04(char* const out_buffer, const int out_buffer_size) {
    float max_english_score = 0;
    unsigned char best_key_char = 0;
    int best_string_index = 0;
    for (int i = 0; i < s04_string_array_size; i++) {
        const char* const input_hex = s04_string_array[i];
        const int byte_buffer_size = hex_to_bytes_size(strlen(input_hex));
        unsigned char byte_buffer[byte_buffer_size];
        if (!hex_to_bytes(input_hex, byte_buffer, byte_buffer_size)) {
            return false;
        }

        float score;
        unsigned char key_char = 0;
        break_single_byte_xor(byte_buffer, byte_buffer_size, 0, 1, &key_char, &score);

        if (score > max_english_score) {
            max_english_score = score;
            best_key_char = key_char;
            best_string_index = i;
        }
    }

    const char* const best_input_hex = s04_string_array[best_string_index];
    const int byte_buffer_size = hex_to_bytes_size(strlen(best_input_hex));
    if (byte_buffer_size + 1 > out_buffer_size) {
        return false;
    }
    unsigned char byte_buffer[byte_buffer_size];
    if (!hex_to_bytes(best_input_hex, byte_buffer, byte_buffer_size)) {
        return false;
    }

    xor_byte(byte_buffer, byte_buffer_size, best_key_char, (unsigned char*)out_buffer, 0, 1);
    out_buffer[byte_buffer_size] = 0;

    return true;
}

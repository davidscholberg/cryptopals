#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "analysis/english_score.h"
#include "ciphers/xor.h"
#include "codecs/hex.h"

// Challenge 3: Decrypt the input message, which has been encrypted with a single repeating
// character via xor.
bool s03(char* const out_buffer, const int out_buffer_size) {
    const char* const input_hex =
        "1b37373331363f78151b7f2b783431333d78397828372d363c78373e783a393b3736";

    const int byte_buffer_size = hex_to_bytes_size(strlen(input_hex));
    unsigned char byte_buffer[byte_buffer_size];
    if (!hex_to_bytes(input_hex, byte_buffer, byte_buffer_size)) {
        return false;
    }

    float max_english_score = 0;
    unsigned char best_candidate_char = 0;
    unsigned char result_buffer[byte_buffer_size];
    for (int i = 0; i <= 255; i++) {
        unsigned char candidate_char = (unsigned char)i;
        if (!xor_byte(
                byte_buffer,
                byte_buffer_size,
                candidate_char,
                result_buffer,
                byte_buffer_size,
                0,
                1
            )) {
            return false;
        }

        float current_english_score = english_score(result_buffer, byte_buffer_size, 0, 1);
        if (current_english_score > max_english_score) {
            max_english_score = current_english_score;
            best_candidate_char = candidate_char;
        }
    }

    if (!xor_byte(
            byte_buffer,
            byte_buffer_size,
            best_candidate_char,
            (unsigned char*)out_buffer,
            out_buffer_size,
            0,
            1
        )) {
        return false;
    }
    out_buffer[byte_buffer_size] = 0;

    return true;
}

#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "analysis/english_score.h"
#include "codecs/hex.h"
#include "codecs/xor.h"
#include "utility/repeat_buffer.h"

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
    unsigned char best_candidate_char;
    unsigned char key_buffer[byte_buffer_size];
    unsigned char result_buffer[byte_buffer_size];
    for (int i = 0; i <= 255; i++) {
        unsigned char candidate_char = (unsigned char)i;
        repeat_buffer(&candidate_char, 1, key_buffer, byte_buffer_size);
        if (!xor_bytes(
                byte_buffer,
                key_buffer,
                byte_buffer_size,
                result_buffer,
                byte_buffer_size
            )) {
            return false;
        }

        float current_english_score = english_score(result_buffer, byte_buffer_size);
        if (current_english_score > max_english_score) {
            max_english_score = current_english_score;
            best_candidate_char = candidate_char;
        }
    }

    repeat_buffer(&best_candidate_char, 1, key_buffer, byte_buffer_size);
    if (!xor_bytes(
            byte_buffer,
            key_buffer,
            byte_buffer_size,
            (unsigned char*)out_buffer,
            out_buffer_size
        )) {
        return false;
    }
    out_buffer[byte_buffer_size] = 0;

    return true;
}

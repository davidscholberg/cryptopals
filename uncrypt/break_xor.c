#include <stdbool.h>

#include "analysis/english_score.h"
#include "ciphers/xor.h"

bool break_single_byte_xor(
    const unsigned char* const input_buffer,
    const int input_buffer_size,
    const int start,
    const int step,
    unsigned char* const key_char,
    float* const score
) {
    float max_english_score = 0;
    unsigned char best_candidate_char = 0;
    unsigned char result_buffer[input_buffer_size];
    for (int i = 0; i <= 255; i++) {
        unsigned char candidate_char = (unsigned char)i;
        if (!xor_byte(
                input_buffer,
                input_buffer_size,
                candidate_char,
                result_buffer,
                input_buffer_size,
                start,
                step
            )) {
            return false;
        }

        float current_english_score = english_score(result_buffer, input_buffer_size, start, step);
        if (current_english_score > max_english_score) {
            max_english_score = current_english_score;
            best_candidate_char = candidate_char;
        }
    }

    *key_char = best_candidate_char;
    if (score) {
        *score = max_english_score;
    }
    return true;
}

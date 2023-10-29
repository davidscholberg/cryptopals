#pragma once

#include <stdbool.h>

// Attempt to break any single-byte xor that may have been applied to the input buffer. Start and
// step represent where to start and how to iterate through the input buffer, respectively. The most
// likely key character found will be placed at key_char, and the score for that key will be placed
// in score.
bool break_single_byte_xor(
    const unsigned char* const input_buffer,
    const int input_buffer_size,
    const int start,
    const int step,
    unsigned char* const key_char,
    float* const score
);

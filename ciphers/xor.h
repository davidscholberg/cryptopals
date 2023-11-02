#pragma once

#include <stdbool.h>

// Take the xor of the input buffer with the input char repeated over it. The start parameter
// indicates an offset for where to start the xor. The step parameter should be set to 1 if you want
// to xor contiguous values in the input buffer, or greater than one if you want to xor values that
// are not contiguous but evenly spaced. Returns true on success, false if result buffer is smaller
// than the input buffer.
bool xor_byte(
    const unsigned char* const input_buffer,
    const int input_buffer_size,
    const unsigned char input_char,
    unsigned char* const result_buffer,
    const int result_buffer_size,
    const int start,
    const int step
);

// Take the xor of the two operand byte arrays and store result in result buffer.
void xor_bytes(
    const unsigned char* const operand1,
    const unsigned char* const operand2,
    unsigned char* const result_buffer,
    const int buffer_size
);

// Take the xor of the input buffer with the key buffer repeated over it. Returns true on success,
// false if result buffer is smaller than the input buffer.
bool xor_repeating_key(
    const unsigned char* const input_buffer,
    const int input_buffer_size,
    const unsigned char* const key_buffer,
    const int key_buffer_size,
    unsigned char* const result_buffer,
    const int result_buffer_size
);

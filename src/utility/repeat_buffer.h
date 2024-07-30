#pragma once

// Place the input buffer into the output buffer repeatedly.
//
// E.g. an input of "ABC" with an output buffer size of 10 would produce "ABCABCABCA".
void repeat_buffer(
    const unsigned char* const input_buffer,
    const int input_buffer_size,
    unsigned char* const output_buffer,
    const int output_buffer_size
);

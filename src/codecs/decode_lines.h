#pragma once

#include <stdbool.h>

// Function type for functions that take an input string and decode it according to the codec that
// it was encoded with. Returns true on success, false if the given output buffer size is not big
// enough to hold the decoded data.
typedef bool (*decode_fn)(const char *const, unsigned char *const, const int);

// Function type for functions that take an encoded string and tell how much space is needed to hold
// the decoded data in the string. Returns true on success, false if the encoded string is invalid.
typedef bool (*decode_size_fn)(const char *const, int *const);

// Take the given encoded text lines and produce an array of decoded buffers with the given decode
// functions. Returns malloced 2D buffer array on success, null on error. Note that freeing the
// returned buffer array will also free the buffer sizes array.
unsigned char **decode_lines(
    char **lines,
    const int line_count,
    decode_fn decode,
    decode_size_fn decode_size,
    int **buffer_sizes_ptr
);

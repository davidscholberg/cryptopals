#pragma once

#include <stdbool.h>

// Tells you how big a string buffer should be to hold an encoded base64 string from a byte buffer
// of size bytes_size. Note that the returned value includes the space needed for a terminating null
// byte.
#define bytes_to_base64_size(bytes_size) (((((bytes_size - 1) / 3) + 1) * 4) + 1)

// Tells you if the given size is a valid size for a base64 encoded string. Note that the given size
// must not include the extra byte needed for a terminating null byte.
#define is_valid_base64_size(base64_size) (base64_size % 4 == 0)

// Decode the given base64 string into a byte array. Returns true on success, false if the size of
// the output buffer is too small or if there's a decoding error. Use the base64_to_bytes_size
// function to get the correct buffer size for the output buffer.
bool base64_to_bytes(
    const char *const base64_string,
    unsigned char *const byte_buffer,
    const int byte_buffer_size
);

// Tells you how big a byte buffer should be to hold the decoded data from the given base64 string.
// Returns true on success, false if the string length is not valid for a base64 string.
bool base64_to_bytes_size(const char *const base64_string, int *const bytes_size);

// Convert byte array to base64 string. Returns true on success, false if the size of the base64
// string buffer is too small. Use the bytes_to_base64_size macro to get the correct buffer size for
// the input bytes.
bool bytes_to_base64(
    const unsigned char *const byte_buffer,
    const int byte_buffer_size,
    char *const base64_buffer,
    const int base64_buffer_size
);

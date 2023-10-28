#pragma once

#include <stdbool.h>

#define bytes_to_base64_size(bytes_size) (((((bytes_size - 1) / 3) + 1) * 4) + 1)

// Convert byte array to base64 string. Returns true on success, false if the size of the base64
// string buffer is too small. Use the bytes_to_base64_size macro to get the correct buffer size for
// the input bytes.
bool bytes_to_base64(
    const unsigned char *const byte_buffer,
    const int byte_buffer_size,
    char *const base64_buffer,
    const int base64_buffer_size
);

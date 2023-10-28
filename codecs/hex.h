#pragma once

#include <stdbool.h>

#define hex_to_bytes_size(hex_size) (hex_size / 2)

// Convert hex string to byte buffer. Returns true on success, false on decoding error or if the
// size of the byte buffer is too small. Use the hex_to_bytes_size macro to get the correct buffer
// size for the input string.
bool hex_to_bytes(
    const char *const hex,
    unsigned char *const byte_buffer,
    const int byte_buffer_size
);

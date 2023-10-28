#pragma once

#include <stdbool.h>

#define bytes_to_hex_size(bytes_size) ((bytes_size * 2) + 1)
#define hex_to_bytes_size(hex_size) (hex_size / 2)

// Convert the given byte array to a hex string and store the string in the given buffer. Returns
// true on success, false if the hex buffer is too small to hold the result. Use the
// bytes_to_hex_size macro to get the correct buffer size for the output string.
bool bytes_to_hex(
    const unsigned char *const byte_buffer,
    const int byte_buffer_size,
    char *const hex_buffer,
    const int hex_buffer_size
);

// Convert hex string to byte buffer. Returns true on success, false on decoding error or if the
// size of the byte buffer is too small. Use the hex_to_bytes_size macro to get the correct buffer
// size for the input string.
bool hex_to_bytes(
    const char *const hex,
    unsigned char *const byte_buffer,
    const int byte_buffer_size
);

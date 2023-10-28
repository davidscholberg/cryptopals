#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "codecs/base64.h"
#include "codecs/hex.h"

// Challenge 1: Convert the given hex string into a base64 string.
bool s01(char* const out_buffer, const int out_buffer_size) {
    const char* const hex_str =
        "49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e6f7573206d75736872"
        "6f6f6d";
    const int hex_str_size = strlen(hex_str);
    const int byte_buffer_size = hex_to_bytes_size(hex_str_size);
    unsigned char byte_buffer[byte_buffer_size];
    if (!hex_to_bytes(hex_str, byte_buffer, byte_buffer_size)) {
        return false;
    }
    return bytes_to_base64(byte_buffer, byte_buffer_size, out_buffer, out_buffer_size);
}

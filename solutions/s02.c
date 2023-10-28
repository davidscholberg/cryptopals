#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "codecs/hex.h"
#include "codecs/xor.h"

// Challenge 2: XOR the decoded bytes of the two hex inputs and hex encode the result.
bool s02(char* const out_buffer, const int out_buffer_size) {
    const char* const input_hex_1 = "1c0111001f010100061a024b53535009181c";
    const char* const input_hex_2 = "686974207468652062756c6c277320657965";
    const int input_hex_size = strlen(input_hex_1);
    const int byte_buffer_size = hex_to_bytes_size(input_hex_size);
    unsigned char input_byte_buffer_1[byte_buffer_size];
    if (!hex_to_bytes(input_hex_1, input_byte_buffer_1, byte_buffer_size)) {
        return false;
    }
    unsigned char input_byte_buffer_2[byte_buffer_size];
    if (!hex_to_bytes(input_hex_2, input_byte_buffer_2, byte_buffer_size)) {
        return false;
    }
    unsigned char xor_byte_buffer[byte_buffer_size];
    if (!xor_bytes(
            input_byte_buffer_1,
            input_byte_buffer_2,
            byte_buffer_size,
            xor_byte_buffer,
            byte_buffer_size
        )) {
        return false;
    }
    return bytes_to_hex(xor_byte_buffer, byte_buffer_size, out_buffer, out_buffer_size);
}

#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "ciphers/xor.h"
#include "codecs/hex.h"
#include "uncrypt/break_xor.h"

// Challenge 3: Decrypt the input message, which has been encrypted with a single repeating
// character via xor.
bool s03(char* const out_buffer, const int out_buffer_size) {
    const char* const input_hex =
        "1b37373331363f78151b7f2b783431333d78397828372d363c78373e783a393b3736";

    const int byte_buffer_size = hex_to_bytes_size(strlen(input_hex));
    unsigned char byte_buffer[byte_buffer_size];
    if (!hex_to_bytes(input_hex, byte_buffer, byte_buffer_size)) {
        return false;
    }

    float score;
    unsigned char key_char = 0;
    if (!break_single_byte_xor(byte_buffer, byte_buffer_size, 0, 1, &key_char, &score)) {
        return false;
    }

    if (!xor_byte(
            byte_buffer,
            byte_buffer_size,
            key_char,
            (unsigned char*)out_buffer,
            out_buffer_size,
            0,
            1
        )) {
        return false;
    }
    out_buffer[byte_buffer_size] = 0;

    return true;
}

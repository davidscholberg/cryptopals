#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "ciphers/xor.h"
#include "codecs/hex.h"

// Challenge 5: Encrypt the given input message with the key "ICE" using repeating key xor.
bool s05(char* const out_buffer, const int out_buffer_size) {
    const char* const input_string =
        "Burning 'em, if you ain't quick and nimble\nI go crazy when I hear a cymbal";
    const char* const key = "ICE";
    const int input_string_size = strlen(input_string);
    unsigned char encrypted_bytes[input_string_size];
    if (!xor_repeating_key(
            (const unsigned char* const)input_string,
            input_string_size,
            (const unsigned char* const)key,
            strlen(key),
            encrypted_bytes,
            input_string_size
        )) {
        return false;
    }

    if (!bytes_to_hex(encrypted_bytes, input_string_size, out_buffer, out_buffer_size)) {
        return false;
    }

    return true;
}

#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "ciphers/aes_cbc.h"
#include "codecs/base64.h"
#include "resources/s10_base64_string.h"

// Challenge 10: Decrypt the input using AES in CBC mode with the given key and iv.
bool s10(char* const out_buffer, const int out_buffer_size) {
    int input_bytes_size = 0;
    if (!base64_to_bytes_size(s10_base64_string, &input_bytes_size)) {
        return false;
    }
    if (input_bytes_size % aes_block_size != 0 || input_bytes_size > out_buffer_size) {
        return false;
    }
    unsigned char input_bytes[input_bytes_size];
    if (!base64_to_bytes(s10_base64_string, input_bytes, input_bytes_size)) {
        return false;
    }

    const char* const key = "YELLOW SUBMARINE";
    const unsigned char iv[aes_block_size] = {0};
    if (!aes_cbc_decrypt(
            input_bytes,
            input_bytes_size,
            (unsigned char* const)out_buffer,
            iv,
            (const unsigned char* const)key
        )) {
        return false;
    }
    out_buffer[input_bytes_size] = 0;
    // cap output at end of first line
    char* const newline = strchr(out_buffer, '\n');
    if (newline) {
        *newline = 0;
    }

    return true;
}

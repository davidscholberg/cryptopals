#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ciphers/aes.h"
#include "codecs/base64.h"
#include "utility/files.h"

// Challenge 10: Decrypt the input using AES in CBC mode with the given key and iv.
bool s10(char* const out_buffer, const int out_buffer_size) {
    char* base64_string = file_to_string("s10_base64_string.txt");
    if (!base64_string) {
        return false;
    }

    int input_bytes_size = 0;
    if (!base64_to_bytes_size(base64_string, &input_bytes_size)) {
        free(base64_string);
        return false;
    }
    if (input_bytes_size % aes_block_size != 0 || input_bytes_size > out_buffer_size) {
        free(base64_string);
        return false;
    }
    if (!base64_to_bytes(base64_string, (unsigned char* const)out_buffer, input_bytes_size)) {
        free(base64_string);
        return false;
    }
    free(base64_string);

    const char* const key = "YELLOW SUBMARINE";
    const unsigned char iv[aes_block_size] = {0};
    if (!aes_cbc_decrypt(
            (unsigned char* const)out_buffer,
            input_bytes_size,
            NULL,
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

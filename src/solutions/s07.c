#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ciphers/aes.h"
#include "codecs/base64.h"
#include "utility/files.h"

#define block_size 16

// Challenge 7: Decrypt the base64-encoded string using AES in ECB mode with key "YELLOW SUBMARINE".
bool s07(char* const out_buffer, const int out_buffer_size) {
    char* base64_string = file_to_string("s07_base64_string.txt");
    if (!base64_string) {
        return false;
    }

    int input_bytes_size = 0;
    if (!base64_to_bytes_size(base64_string, &input_bytes_size)) {
        free(base64_string);
        return false;
    }
    if (input_bytes_size % block_size != 0 || input_bytes_size > out_buffer_size) {
        free(base64_string);
        return false;
    }
    if (!base64_to_bytes(base64_string, (unsigned char* const)out_buffer, input_bytes_size)) {
        free(base64_string);
        return false;
    }
    free(base64_string);

    const char* const key = "YELLOW SUBMARINE";
    if (!aes_ecb_decrypt(
            (unsigned char* const)out_buffer,
            input_bytes_size,
            NULL,
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

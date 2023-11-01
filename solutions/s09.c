#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "codecs/hex.h"
#include "utility/pkcs7_pad.h"

#define block_size 20

// Challenge 9: PKCS7 pad the given input to 20 bytes.
bool s09(char* const out_buffer, __attribute__((unused)) const int out_buffer_size) {
    const char* const input_buffer = "YELLOW SUBMARINE";
    int input_buffer_length = strlen(input_buffer);
    int padded_buffer_size =
        input_buffer_length + pkcs7_padding_needed(input_buffer_length, block_size);
    unsigned char padded_buffer[padded_buffer_size];
    pkcs7_pad(
        (const unsigned char* const)input_buffer,
        padded_buffer,
        input_buffer_length,
        block_size
    );

    if (!bytes_to_hex(padded_buffer, padded_buffer_size, out_buffer, out_buffer_size)) {
        return false;
    }
    return true;
}

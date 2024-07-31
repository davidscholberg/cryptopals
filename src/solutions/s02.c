#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "ciphers/xor.h"
#include "codecs/hex.h"
#include "log.h"

// Challenge 2: XOR the decoded bytes of the two hex inputs and hex encode the result.
bool s02(char* const out_buffer, const int out_buffer_size) {
    bool status = false;

    const char* const input_hex_1 = "1c0111001f010100061a024b53535009181c";
    const char* const input_hex_2 = "686974207468652062756c6c277320657965";
    const int input_hex_size = strlen(input_hex_1);

    const int byte_buffer_size = hex_to_bytes_size(input_hex_size);
    unsigned char* const byte_buffers = malloc(byte_buffer_size * 3);
    if (!byte_buffers) {
        log_error("malloc failed");
        goto s02_exit;
    }

    unsigned char* const input_byte_buffer_1 = byte_buffers;
    unsigned char* const input_byte_buffer_2 = byte_buffers + byte_buffer_size;
    unsigned char* const xor_byte_buffer = byte_buffers + (2 * byte_buffer_size);

    if (!hex_to_bytes(input_hex_1, input_byte_buffer_1, byte_buffer_size)) {
        goto s02_cleanup_byte_buffers;
    }
    if (!hex_to_bytes(input_hex_2, input_byte_buffer_2, byte_buffer_size)) {
        goto s02_cleanup_byte_buffers;
    }

    xor_bytes(input_byte_buffer_1, input_byte_buffer_2, xor_byte_buffer, byte_buffer_size);
    status = bytes_to_hex(xor_byte_buffer, byte_buffer_size, out_buffer, out_buffer_size);

s02_cleanup_byte_buffers:
    free(byte_buffers);

s02_exit:
    return status;
}

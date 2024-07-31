#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "ciphers/xor.h"
#include "codecs/hex.h"
#include "log.h"
#include "uncrypt/break_xor.h"

// Challenge 3: Decrypt the input message, which has been encrypted with a single repeating
// character via xor.
bool s03(char* const out_buffer, const int out_buffer_size) {
    bool status = false;
    const char* const input_hex =
        "1b37373331363f78151b7f2b783431333d78397828372d363c78373e783a393b3736";

    const int byte_buffer_size = hex_to_bytes_size(strlen(input_hex));
    if (byte_buffer_size + 1 > out_buffer_size) {
        log_error("out buffer not big enough");
        goto s03_exit;
    }

    unsigned char* const byte_buffers = malloc(byte_buffer_size * 2);
    if (!byte_buffers) {
        log_error("malloc failed");
        goto s03_exit;
    }

    unsigned char* const input_byte_buffer = byte_buffers;
    unsigned char* const result_buffer = byte_buffers + byte_buffer_size;

    if (!hex_to_bytes(input_hex, input_byte_buffer, byte_buffer_size)) {
        goto s03_cleanup_byte_buffers;
    }

    float score;
    unsigned char key_char = 0;
    break_single_byte_xor(input_byte_buffer, byte_buffer_size, result_buffer, 0, 1, &key_char, &score);

    xor_byte(input_byte_buffer, byte_buffer_size, key_char, (unsigned char*)out_buffer, 0, 1);
    out_buffer[byte_buffer_size] = 0;

    status = true;

s03_cleanup_byte_buffers:
    free(byte_buffers);

s03_exit:
    return status;
}

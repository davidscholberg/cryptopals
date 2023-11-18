#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ciphers/aes.h"
#include "ciphers/xor.h"
#include "codecs/base64.h"
#include "codecs/decode_lines.h"
#include "uncrypt/break_ctr.h"
#include "utility/files.h"

// Challenge 19: Take the given list of base64 strings, decode them, encrypt them with AES CTR using
// a fixed nonce and key, and then decrypt the strings using only the ciphertexts.
bool s19(char* const out_buffer, const int out_buffer_size) {
    int line_count = 0;
    char** lines = file_to_lines("s19_base64_string_array.txt", &line_count);
    if (!lines) {
        return false;
    }

    int* buffer_sizes = 0;
    unsigned char** buffers =
        decode_lines(lines, line_count, base64_to_bytes, base64_to_bytes_size, &buffer_sizes);
    free(lines);
    if (!buffers) {
        return false;
    }

    const char* const key = "ice ice baby ice";
    const unsigned char iv[aes_block_size] = {0};
    for (int i = 0; i < line_count; i++) {
        aes_ctr_encrypt(buffers[i], buffer_sizes[i], NULL, iv, (const unsigned char* const)key);
    }

    int max_buffer_size = 0;
    for (int i = 0; i < line_count; i++) {
        if (buffer_sizes[i] > max_buffer_size) {
            max_buffer_size = buffer_sizes[i];
        }
    }

    unsigned char keystream[max_buffer_size];
    break_fixed_nonce_ctr(
        (const unsigned char** const)buffers,
        buffer_sizes,
        line_count,
        keystream
    );

    char* out_buffer_ptr = out_buffer;
    for (int i = 0; i < line_count; i++) {
        const int current_buffer_size = buffer_sizes[i];
        if ((out_buffer_ptr - out_buffer) + current_buffer_size + 1 > out_buffer_size) {
            free(buffers);
            return false;
        }

        xor_bytes(buffers[i], keystream, (unsigned char* const)out_buffer_ptr, current_buffer_size);
        out_buffer_ptr[current_buffer_size] = '\n';
        out_buffer_ptr += current_buffer_size + 1;
    }

    free(buffers);

    *out_buffer_ptr = 0;

    // Cap output at first newline.
    char* newline = strchr(out_buffer, '\n');
    if (newline) {
        *newline = 0;
    }

    return true;
}

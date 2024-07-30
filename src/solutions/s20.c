#include <limits.h>
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

// Challenge 20: Take the given list of base64 strings, decode them, encrypt them with AES CTR using
// a fixed nonce and key, and then decrypt the strings using only the ciphertexts. Note that this
// solution is identical to the previous one because I inadvertently did it (nearly) the right way
// for challenge 19 instead of the dumb way that challenge 19 apparently wanted.
bool s20(char* const out_buffer, const int out_buffer_size) {
    int line_count = 0;
    char** lines = file_to_lines("s20_base64_string_array.txt", &line_count);
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
        aes_ctr_encrypt(buffers[i], buffer_sizes[i], NULL, iv, (const unsigned char* const)key, 0);
    }

    int max_common_buffer_size = INT_MAX;
    for (int i = 0; i < line_count; i++) {
        if (buffer_sizes[i] < max_common_buffer_size) {
            max_common_buffer_size = buffer_sizes[i];
        }
    }
    if ((max_common_buffer_size * line_count) + line_count + 1 > out_buffer_size) {
        free(buffers);
        return false;
    }

    unsigned char keystream[max_common_buffer_size];
    break_fixed_nonce_ctr(
        (const unsigned char** const)buffers,
        line_count,
        max_common_buffer_size,
        keystream
    );

    char* out_buffer_ptr = out_buffer;
    for (int i = 0; i < line_count; i++) {
        xor_bytes(
            buffers[i],
            keystream,
            (unsigned char* const)out_buffer_ptr,
            max_common_buffer_size
        );
        out_buffer_ptr[max_common_buffer_size] = '\n';
        out_buffer_ptr += max_common_buffer_size + 1;
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

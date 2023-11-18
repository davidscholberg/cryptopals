#include <limits.h>

#include "analysis/english_score.h"
#include "ciphers/xor.h"

void break_fixed_nonce_ctr(
    const unsigned char** const buffers,
    const int* const buffer_sizes,
    const int buffer_count,
    unsigned char* const keystream
) {
    // Get the maximum buffer length.
    int max_buffer_size = 0;
    for (int i = 0; i < buffer_count; i++) {
        if (buffer_sizes[i] > max_buffer_size) {
            max_buffer_size = buffer_sizes[i];
        }
    }

    // This buffer represents all values in the ciphertext buffers that were xored with the same
    // keystream byte.
    unsigned char shared_keystream_ciphertext_buffer[buffer_count];
    unsigned char shared_keystream_xored_buffer[buffer_count];

    for (int keystream_i = 0; keystream_i < max_buffer_size; keystream_i++) {
        // Copy ciphertext bytes into shared_keystream_ciphertext_buffer
        int shared_keystream_buffer_i = 0;
        for (int buffer_i = 0; buffer_i < buffer_count; buffer_i++) {
            if (keystream_i < buffer_sizes[buffer_i]) {
                shared_keystream_ciphertext_buffer[shared_keystream_buffer_i] =
                    buffers[buffer_i][keystream_i];
                shared_keystream_buffer_i++;
            }
        }

        // Find most likely keystream byte via english scoring
        float max_english_score = 0;
        for (int byte_value = 0; byte_value <= UCHAR_MAX; byte_value++) {
            xor_byte(
                shared_keystream_ciphertext_buffer,
                shared_keystream_buffer_i,
                byte_value,
                shared_keystream_xored_buffer,
                0,
                1
            );

            float current_english_score =
                english_score(shared_keystream_xored_buffer, shared_keystream_buffer_i, 0, 1);
            if (current_english_score > max_english_score) {
                max_english_score = current_english_score;
                keystream[keystream_i] = byte_value;
            }
        }
    }
}

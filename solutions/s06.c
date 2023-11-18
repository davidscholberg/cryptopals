#include <float.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "analysis/hamming_distance.h"
#include "ciphers/xor.h"
#include "codecs/base64.h"
#include "resources/s06_base64_string.h"
#include "uncrypt/break_xor.h"

#define min_key_size_to_check 2
#define max_key_size_to_check 40

// Challenge 6: Break the repeating key xor of the given input.
bool s06(char* const out_buffer, const int out_buffer_size) {
    int input_bytes_size = 0;
    if (!base64_to_bytes_size(s06_base64_string, &input_bytes_size)) {
        return false;
    }
    unsigned char input_bytes[input_bytes_size];
    if (!base64_to_bytes(s06_base64_string, input_bytes, input_bytes_size)) {
        return false;
    }

    int best_guess_key_size = 0;
    float lowest_hamming_distance = FLT_MAX;
    for (int key_size = min_key_size_to_check; key_size <= max_key_size_to_check; key_size++) {
        float hamming_distance =
            adjacent_blocks_hamming_distance(input_bytes, input_bytes_size, key_size);
        if (hamming_distance != -1 && hamming_distance < lowest_hamming_distance) {
            lowest_hamming_distance = hamming_distance;
            best_guess_key_size = key_size;
        }
    }
    if (best_guess_key_size + 1 > out_buffer_size) {
        return false;
    }

    for (int i = 0; i < best_guess_key_size; i++) {
        break_single_byte_xor(
            input_bytes,
            input_bytes_size,
            i,
            best_guess_key_size,
            &(((unsigned char* const)out_buffer)[i]),
            NULL
        );
    }
    out_buffer[best_guess_key_size] = 0;

    return true;
}

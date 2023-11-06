#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "analysis/repeating_blocks.h"
#include "utility/oracles.h"

// Challenge 12:
bool s12(char* const out_buffer, const int out_buffer_size) {
    // Determine block size and unknown string size.
    int determined_block_size = 0;
    int unknown_string_size = 0;
    const int intital_buffer_size = aes_ecb_oracle_size(1);
    for (int data_size = 2; data_size <= 20; data_size++) {
        const int current_buffer_size = aes_ecb_oracle_size(data_size);
        if (current_buffer_size > intital_buffer_size) {
            determined_block_size = current_buffer_size - intital_buffer_size;
            unknown_string_size = current_buffer_size - determined_block_size - data_size;
            break;
        }
    }
    if (unknown_string_size >= out_buffer_size) {
        return false;
    }

    // Ensure that the oracle uses ECB.
    const int detect_ecb_buffer_size = determined_block_size * 2;
    unsigned char detect_ecb_buffer[detect_ecb_buffer_size];
    for (int i = 0; i < detect_ecb_buffer_size; i++) {
        detect_ecb_buffer[i] = 0;
    }
    const int detect_ecb_output_buffer_size = aes_ecb_oracle_size(detect_ecb_buffer_size);
    unsigned char detect_ecb_output_buffer[detect_ecb_output_buffer_size];
    if (!aes_ecb_oracle(detect_ecb_buffer, detect_ecb_buffer_size, detect_ecb_output_buffer)) {
        return false;
    }
    if (!repeating_blocks(
            detect_ecb_output_buffer,
            detect_ecb_buffer_size,
            determined_block_size
        )) {
        return false;
    }

    // Decrypt unknown string.
    const int total_spacer_data_size = unknown_string_size +
        (determined_block_size - (unknown_string_size % determined_block_size));
    unsigned char spacer_data[total_spacer_data_size];
    for (int i = 0; i < total_spacer_data_size; i++) {
        spacer_data[i] = 0;
    }

    const int encrypted_spacer_data_size = aes_ecb_oracle_size(total_spacer_data_size);
    unsigned char encrypted_spacer_data[encrypted_spacer_data_size];
    const unsigned char* const encrypted_spacer_edge_block =
        encrypted_spacer_data + total_spacer_data_size - determined_block_size;

    unsigned char comparison_block_input[determined_block_size];
    for (int i = 0; i < determined_block_size; i++) {
        comparison_block_input[i] = 0;
    }
    const int comparison_block_output_size = aes_ecb_oracle_size(determined_block_size);
    unsigned char comparison_block_output[comparison_block_output_size];

    for (int i = 1; i <= unknown_string_size; i++) {
        const int spacer_data_size = total_spacer_data_size - i;
        if (!aes_ecb_oracle(spacer_data, spacer_data_size, encrypted_spacer_data)) {
            return false;
        }

        const int unknown_string_index = i - 1;
        for (int byte_value = 0; byte_value <= UCHAR_MAX; byte_value++) {
            comparison_block_input[determined_block_size - 1] = byte_value;
            if (!aes_ecb_oracle(
                    comparison_block_input,
                    determined_block_size,
                    comparison_block_output
                )) {
                return false;
            }
            if (!memcmp(
                    encrypted_spacer_edge_block,
                    comparison_block_output,
                    determined_block_size
                )) {
                out_buffer[unknown_string_index] = (unsigned char)byte_value;
                break;
            }
        }

        for (int j = 0; j < determined_block_size - 1; j++) {
            comparison_block_input[j] = comparison_block_input[j + 1];
        }
    }

    out_buffer[unknown_string_size] = 0;

    return true;
}

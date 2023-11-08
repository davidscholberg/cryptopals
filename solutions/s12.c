#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "analysis/oracle_info.h"
#include "utility/oracles.h"

// Challenge 12: Decrypt the string that's being appended to the input of the encryption oracle.
bool s12(char* const out_buffer, const int out_buffer_size) {
    int block_size = 0;
    int unknown_string_size = 0;
    bool is_using_ecb = false;
    if (!oracle_info(
            aes_ecb_oracle,
            aes_ecb_oracle_size,
            &block_size,
            &unknown_string_size,
            &is_using_ecb,
            NULL,
            NULL
        )) {
        return false;
    }
    if (!is_using_ecb || unknown_string_size >= out_buffer_size) {
        return false;
    }

    // Decrypt unknown string.
    const int total_spacer_data_size =
        unknown_string_size + (block_size - (unknown_string_size % block_size));
    unsigned char spacer_data[total_spacer_data_size];
    for (int i = 0; i < total_spacer_data_size; i++) {
        spacer_data[i] = 0;
    }

    const int encrypted_spacer_data_size = aes_ecb_oracle_size(total_spacer_data_size);
    unsigned char encrypted_spacer_data[encrypted_spacer_data_size];
    const unsigned char* const encrypted_spacer_edge_block =
        encrypted_spacer_data + total_spacer_data_size - block_size;

    unsigned char comparison_block_input[block_size];
    for (int i = 0; i < block_size; i++) {
        comparison_block_input[i] = 0;
    }
    const int comparison_block_output_size = aes_ecb_oracle_size(block_size);
    unsigned char comparison_block_output[comparison_block_output_size];

    for (int i = 1; i <= unknown_string_size; i++) {
        const int spacer_data_size = total_spacer_data_size - i;
        if (!aes_ecb_oracle(spacer_data, spacer_data_size, encrypted_spacer_data)) {
            return false;
        }

        const int unknown_string_index = i - 1;
        for (int byte_value = 0; byte_value <= UCHAR_MAX; byte_value++) {
            comparison_block_input[block_size - 1] = byte_value;
            if (!aes_ecb_oracle(comparison_block_input, block_size, comparison_block_output)) {
                return false;
            }
            if (!memcmp(encrypted_spacer_edge_block, comparison_block_output, block_size)) {
                out_buffer[unknown_string_index] = (unsigned char)byte_value;
                break;
            }
        }

        for (int j = 0; j < block_size - 1; j++) {
            comparison_block_input[j] = comparison_block_input[j + 1];
        }
    }

    out_buffer[unknown_string_size] = 0;

    return true;
}

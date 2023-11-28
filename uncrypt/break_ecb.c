#include <limits.h>
#include <string.h>

#include "analysis/oracle_info.h"

int break_ecb(
    block_cipher_oracle_fn oracle,
    block_cipher_oracle_size_fn oracle_size,
    unsigned char* const output_buffer,
    const int output_buffer_size
) {
    int block_size = 0;
    int added_data_size = 0;
    bool is_using_ecb = false;
    int prefix_size = 0;
    int suffix_size = 0;
    if (!block_cipher_oracle_info(
            oracle,
            oracle_size,
            &block_size,
            &added_data_size,
            &is_using_ecb,
            &prefix_size,
            &suffix_size
        )) {
        return -1;
    }
    if (!is_using_ecb || suffix_size > output_buffer_size) {
        return -1;
    }
    if (suffix_size == 0) {
        return 0;
    }

    // Decrypt suffix string.
    const int total_spacer_data_size = suffix_size + (block_size - (added_data_size % block_size));
    unsigned char spacer_data[total_spacer_data_size];
    for (int i = 0; i < total_spacer_data_size; i++) {
        spacer_data[i] = 0;
    }

    const int encrypted_spacer_data_size = oracle_size(total_spacer_data_size);
    unsigned char encrypted_spacer_data[encrypted_spacer_data_size];
    const unsigned char* const encrypted_spacer_edge_block =
        encrypted_spacer_data + total_spacer_data_size + prefix_size - block_size;

    const int comparison_input_buffer_size = block_size + (block_size - (prefix_size % block_size));
    unsigned char comparison_input_buffer[comparison_input_buffer_size];
    unsigned char* const comparison_input_block =
        comparison_input_buffer + comparison_input_buffer_size - block_size;
    for (int i = 0; i < block_size; i++) {
        comparison_input_block[i] = 0;
    }
    const int comparison_output_buffer_size = oracle_size(comparison_input_buffer_size);
    unsigned char comparison_output_buffer[comparison_output_buffer_size];
    const unsigned char* const comparison_output_block =
        comparison_output_buffer + prefix_size + comparison_input_buffer_size - block_size;

    for (int i = 1; i <= suffix_size; i++) {
        const int spacer_data_size = total_spacer_data_size - i;
        if (!oracle(spacer_data, spacer_data_size, encrypted_spacer_data)) {
            return -1;
        }

        const int suffix_string_index = i - 1;
        for (int byte_value = 0; byte_value <= UCHAR_MAX; byte_value++) {
            comparison_input_block[block_size - 1] = byte_value;
            if (!oracle(
                    comparison_input_buffer,
                    comparison_input_buffer_size,
                    comparison_output_buffer
                )) {
                return -1;
            }
            if (!memcmp(encrypted_spacer_edge_block, comparison_output_block, block_size)) {
                output_buffer[suffix_string_index] = (unsigned char)byte_value;
                break;
            }
        }

        for (int j = 0; j < block_size - 1; j++) {
            comparison_input_block[j] = comparison_input_block[j + 1];
        }
    }

    return suffix_size;
}

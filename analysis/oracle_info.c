#include <stdbool.h>
#include <string.h>

#include "oracle_info.h"
#include "repeating_blocks.h"

#define key_size_min 8
#define key_size_max 32

bool oracle_info(
    oracle_fn oracle,
    oracle_size_fn oracle_size,
    int* const block_size,
    int* const added_data_size,
    bool* const is_using_ecb,
    int* const prefix_size,
    int* const suffix_size
) {
    // Determine block size and optionally added data size.
    const int intital_buffer_size = oracle_size(key_size_min - 1);
    for (int data_size = key_size_min; data_size <= key_size_max; data_size++) {
        const int current_buffer_size = oracle_size(data_size);
        if (current_buffer_size > intital_buffer_size) {
            *block_size = current_buffer_size - intital_buffer_size;
            if (added_data_size) {
                *added_data_size = current_buffer_size - *block_size - data_size;
            }
            break;
        }
    }

    // Optionally determine if the oracle uses ecb mode.
    if (is_using_ecb) {
        const int input_buffer_size = *block_size * 3;
        unsigned char input_buffer[input_buffer_size];
        for (int i = 0; i < input_buffer_size; i++) {
            input_buffer[i] = 0;
        }
        const int output_buffer_size = oracle_size(input_buffer_size);
        unsigned char output_buffer[output_buffer_size];
        if (!oracle(input_buffer, input_buffer_size, output_buffer)) {
            return false;
        }
        const int repeating_block_count =
            repeating_blocks(output_buffer, output_buffer_size, *block_size);
        *is_using_ecb = repeating_block_count == 2 || repeating_block_count == 3;
    }

    // Optionally determine prefix and suffix size.
    if (is_using_ecb && *is_using_ecb && prefix_size) {
        *prefix_size = -1;

        const int input_buffer_size = *block_size * 3;
        unsigned char input_buffer[input_buffer_size];
        for (int i = 0; i < input_buffer_size; i++) {
            input_buffer[i] = 0;
        }
        const int output_buffer_size = oracle_size(input_buffer_size);
        unsigned char output_buffer[output_buffer_size];
        for (int i = 0; i < *block_size; i++) {
            const int current_input_size = (*block_size * 2) + i;
            if (!oracle(input_buffer, current_input_size, output_buffer)) {
                return false;
            }

            const int current_output_size = oracle_size(current_input_size);
            const int block_count = current_output_size / *block_size;
            for (int block_index = 0; block_index < block_count - 1; block_index++) {
                const unsigned char* const block_a = output_buffer + (*block_size * block_index);
                const unsigned char* const block_b = block_a + *block_size;
                if (!memcmp(block_a, block_b, *block_size)) {
                    *prefix_size = ((block_index - 1) * *block_size) + *block_size - i;
                    break;
                }
            }

            if (*prefix_size != -1) {
                break;
            }
        }

        if (added_data_size && suffix_size) {
            *suffix_size = *added_data_size - *prefix_size;
        }
    }

    return true;
}

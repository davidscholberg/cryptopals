#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "analysis/repeating_blocks.h"
#include "utility/oracles.h"
#include "utility/pkcs7_pad.h"

// Challenge 13: Create a profile with the admin role using ECB cut and paste.
bool s13(char* const out_buffer, const int out_buffer_size) {
    // Determine block size and added data size.
    int block_size = 0;
    int added_data_size = 0;
    const int intital_buffer_size = encrypted_profile_oracle_size(1);
    for (int data_size = 2; data_size <= 20; data_size++) {
        const int current_buffer_size = encrypted_profile_oracle_size(data_size);
        if (current_buffer_size > intital_buffer_size) {
            block_size = current_buffer_size - intital_buffer_size;
            added_data_size = current_buffer_size - block_size - data_size;
            break;
        }
    }

    // Determine prefix size (currently assumes that the prefix is less than or equal to block
    // size).
    int prefix_size = 0;
    const int prefix_guess_input_max_size = block_size * 3;
    unsigned char prefix_guess_input[prefix_guess_input_max_size];
    for (int i = 0; i < prefix_guess_input_max_size; i++) {
        prefix_guess_input[i] = 0;
    }
    const int prefix_guess_output_max_size =
        encrypted_profile_oracle_size(prefix_guess_input_max_size);
    unsigned char prefix_guess_output[prefix_guess_output_max_size];
    const unsigned char* const prefix_guess_output_block_2 = prefix_guess_output + block_size;
    const unsigned char* const prefix_guess_output_block_3 = prefix_guess_output + (block_size * 2);
    for (int i = 0; i <= block_size; i++) {
        if (!encrypted_profile_oracle(
                prefix_guess_input,
                (block_size * 2) + i,
                prefix_guess_output
            )) {
            return false;
        }

        if (!memcmp(prefix_guess_output_block_2, prefix_guess_output_block_3, block_size)) {
            prefix_size = block_size - i;
            break;
        }
    }

    // Craft an input to get the output block for the string "admin" with pkcs7 padding.
    const char* const admin_string = "admin";
    const int admin_string_size = strlen(admin_string);
    const int padded_admin_input_size = (block_size * 2) - prefix_size;
    unsigned char padded_admin_input[padded_admin_input_size];
    unsigned char* const padded_admin_block_boundary =
        padded_admin_input + block_size - prefix_size;
    memcpy(padded_admin_block_boundary, admin_string, admin_string_size);
    pkcs7_pad(padded_admin_block_boundary, NULL, admin_string_size, block_size);
    const int padded_admin_output_size = encrypted_profile_oracle_size(padded_admin_input_size);
    unsigned char padded_admin_output[padded_admin_output_size];
    if (!encrypted_profile_oracle(
            padded_admin_input,
            padded_admin_input_size,
            padded_admin_output
        )) {
        return false;
    }
    unsigned char encrypted_admin_block[block_size];
    memcpy(encrypted_admin_block, padded_admin_output + block_size, block_size);

    // Craft an input to put the role name alone in the last block, then copy the encrypted admin
    // block over this last block.
    const int final_input_size = (block_size * 2) - added_data_size + 4;
    unsigned char final_input[final_input_size];
    const char* const final_input_suffix = "@a.com";
    const int final_input_suffix_size = strlen(final_input_suffix);
    const int final_input_prefix_size = final_input_size - final_input_suffix_size;
    for (int i = 0; i < final_input_size; i++) {
        if (i < final_input_prefix_size) {
            final_input[i] = 'a';
        } else {
            final_input[i] = final_input_suffix[i - final_input_prefix_size];
        }
    }
    const int final_output_size = encrypted_profile_oracle_size(final_input_size);
    if (final_output_size >= out_buffer_size) {
        return false;
    }
    unsigned char final_output[final_output_size];
    if (!encrypted_profile_oracle(final_input, final_input_size, final_output)) {
        return false;
    }
    memcpy(final_output + (block_size * 2), encrypted_admin_block, block_size);
    if (!encrypted_profile_decrypt(
            final_output,
            final_output_size,
            (unsigned char* const)out_buffer
        )) {
        return false;
    }

    out_buffer[final_output_size - pkcs7_padding_size(out_buffer, final_output_size)] = 0;

    return true;
}

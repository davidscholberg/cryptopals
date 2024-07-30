#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "analysis/oracle_info.h"
#include "oracles/ecb_oracles.h"
#include "utility/pkcs7_pad.h"

// Challenge 13: Create a profile with the admin role using ECB cut and paste.
bool s13(char* const out_buffer, const int out_buffer_size) {
    int block_size = 0;
    int added_data_size = 0;
    bool is_using_ecb = false;
    int prefix_size = 0;
    if (!block_cipher_oracle_info(
            encrypted_profile_oracle,
            encrypted_profile_oracle_size,
            &block_size,
            &added_data_size,
            &is_using_ecb,
            &prefix_size,
            NULL
        )) {
        return false;
    }
    if (!is_using_ecb) {
        return false;
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

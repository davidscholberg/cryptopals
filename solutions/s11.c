#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "analysis/repeating_blocks.h"
#include "ciphers/aes.h"
#include "utility/oracles.h"

#define plaintext_size 100
#define passes 10

// Challenge 11: Create function that randomly encrypts with ECB or CBC and detect which mode it
// uses.
bool s11(char* const out_buffer, const int out_buffer_size) {
    const unsigned char plaintext[plaintext_size] = {0};
    unsigned char ciphertext[aes_ecb_cbc_oracle_max_size_needed(plaintext_size)];
    cipher_mode used_cipher_mode = ecb;
    bool passed = true;
    for (int i = 0; i < passes; i++) {
        const int oracle_output_size =
            aes_ecb_cbc_oracle(plaintext, plaintext_size, ciphertext, &used_cipher_mode);
        if (oracle_output_size == -1) {
            return false;
        }

        cipher_mode guessed_cipher_mode = cbc;
        if (repeating_blocks(ciphertext, oracle_output_size, aes_block_size)) {
            guessed_cipher_mode = ecb;
        }

        if (guessed_cipher_mode != used_cipher_mode) {
            passed = false;
            break;
        }
    }

    if (passed) {
        strncpy(out_buffer, "guessed all cipher modes correctly", out_buffer_size);
    } else {
        strncpy(out_buffer, "incorrectly guessed cipher mode", out_buffer_size);
    }

    return true;
}

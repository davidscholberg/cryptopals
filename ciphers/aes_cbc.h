#pragma once

#include <stdbool.h>

#define aes_block_size 16

// Decrypt ciphertext with aes using cbc mode. Returns true on success, false if the ciphertext size
// is not at least as large as one block.
bool aes_cbc_decrypt(
    const unsigned char* const ciphertext,
    const int ciphertext_size,
    unsigned char* const plaintext,
    const unsigned char* const iv,
    const unsigned char* const key
);

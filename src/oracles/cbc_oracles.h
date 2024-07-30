#pragma once

#include <stdbool.h>

// Encrypts an unknown string with an unknown key using AES CBC and gives the iv. The given
// ciphertext buffer should already have the space needed to hold the ciphertext, which can be
// determined with the aes_cbc_unknown_plaintext_oracle_size function. Returns true on success,
// false on encryption error.
bool aes_cbc_unknown_plaintext_oracle(unsigned char* const ciphertext, unsigned char* const iv);

// Returns the amount of space needed to hold the iv used for aes_cbc_unknown_plaintext_oracle.
int aes_cbc_unknown_plaintext_oracle_iv_size(void);

// Returns the amount of space needed to hold the output of aes_cbc_unknown_plaintext_oracle.
int aes_cbc_unknown_plaintext_oracle_size(void);

// Decrypt the given buffer under the secret key used to encrypt it with
// aes_cbc_unknown_plaintext_oracle and verify whether or not the padding is valid. Returns true on
// success and false on decryption error.
bool aes_cbc_unknown_plaintext_oracle_verify_padding(
    unsigned char* const ciphertext,
    const int ciphertext_size,
    const unsigned char* const iv,
    const int iv_size,
    bool* const padding_is_valid
);

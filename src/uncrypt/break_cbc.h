#pragma once

#include <stdbool.h>

// Function type for a function that takes a ciphertext, decrypts it with the key it was
// encrypted with and the given iv via AES CBC, and verifies that the pkcs7 padding at the end is
// valid.
typedef bool (*padding_oracle_fn)(
    unsigned char* const,
    const int,
    const unsigned char* const,
    const int,
    bool* const
);

// Given the padding oracle, ciphertext, and iv, decrypt the ciphertext. The plaintext buffer should
// be at least equal in size to the ciphertext buffer.
bool break_cbc_padding_oracle(
    padding_oracle_fn padding_oracle,
    const unsigned char* const ciphertext,
    const int ciphertext_size,
    const unsigned char* const iv,
    const int iv_size,
    unsigned char* const plaintext
);

#pragma once

#include <stdbool.h>

#include "ciphers/aes.h"
#include "pkcs7_pad.h"

typedef enum cipher_mode { ecb, cbc } cipher_mode;

#define aes_ecb_cbc_oracle_min_prepend 5
#define aes_ecb_cbc_oracle_max_prepend 10
#define aes_ecb_cbc_oracle_min_append 5
#define aes_ecb_cbc_oracle_max_append 10

#define aes_ecb_cbc_oracle_max_size_needed(buffer_size)                \
    (buffer_size + pkcs7_padding_needed(buffer_size, aes_block_size) + \
     aes_ecb_cbc_oracle_max_prepend + aes_ecb_cbc_oracle_max_append)

// Take the given plaintext, prepend and append 5-10 bytes per end, pkcs7 pad the result, and
// encrypt the whole thing with a random key using either ECB mode or CBC mode (chosen randomly).
// Returns the size of the resulting buffer or -1 if there was an encryption error. The given
// ciphertext buffer must already have the necessary space allocated for the added bytes and
// padding; use the aes_ecb_cbc_oracle_max_size_needed macro to get the maximum amount of space
// needed.
int aes_ecb_cbc_oracle(
    const unsigned char* const plaintext,
    const int plaintext_size,
    unsigned char* const ciphertext,
    cipher_mode* const cipher_mode_used
);

// Take the given plaintext, append a constant but unknown string to it, pkcs7 pad it, and encrypt
// the whole thing via AES ECB with a constant but unknown key. The given ciphertext buffer must
// already have the needed amount of space, which you can determine with the aes_ecb_oracle_size
// function. The given plaintext_size should not include the extra space needed for the unknown
// string.
bool aes_ecb_oracle(
    const unsigned char* const plaintext,
    const int plaintext_size,
    unsigned char* const ciphertext
);

// Returns the amount of space needed to hold the output of aes_ecb_oracle with the given input
// size.
int aes_ecb_oracle_size(const int plaintext_size);
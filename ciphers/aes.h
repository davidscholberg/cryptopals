#pragma once

#include <stdbool.h>

#define aes_block_size 16

// Decrypt ciphertext with aes using cbc mode. If plaintext is null, decryption happens in place.
// Returns true on success, false if the ciphertext size is not at least as large as one block.
bool aes_cbc_decrypt(
    unsigned char* const ciphertext,
    const int ciphertext_size,
    unsigned char* plaintext,
    const unsigned char* const iv,
    const unsigned char* const key
);

// Encrypt plaintext with aes using cbc mode. If ciphertext is null, encryption happens in place.
// Returns true on success, false if the plaintext size is not at least as large as one block.
bool aes_cbc_encrypt(
    unsigned char* const plaintext,
    const int plaintext_size,
    unsigned char* ciphertext,
    const unsigned char* const iv,
    const unsigned char* const key
);

// Decrypt ciphertext with aes using ctr mode. If plaintext is null, decryption happens in place. If
// offset is greater than zero, decryption will start at that offset into the ciphertext without
// changing what the keystream would be at that point.
void aes_ctr_decrypt(
    unsigned char* const ciphertext,
    const int ciphertext_size,
    unsigned char* plaintext,
    const unsigned char* const iv,
    const unsigned char* const key,
    const int offset
);

// Encrypt plaintext with aes using ctr mode. If ciphertext is null, encryption happens in place. If
// offset is greater than zero, encryption will start at that offset into the plaintext without
// changing what the keystream would be at that point.
void aes_ctr_encrypt(
    unsigned char* const plaintext,
    const int plaintext_size,
    unsigned char* ciphertext,
    const unsigned char* const iv,
    const unsigned char* const key,
    const int offset
);

// Decrypt ciphertext with aes using ecb mode. If plaintext is null, decryption happens in place.
// Returns true on success, false if the ciphertext size is not at least as large as one block.
bool aes_ecb_decrypt(
    unsigned char* const ciphertext,
    const int ciphertext_size,
    unsigned char* plaintext,
    const unsigned char* const key
);

// Encrypt plaintext with aes using ecb mode. If ciphertext is null, encryption happens in place.
// Returns true on success, false if the plaintext size is not at least as large as one block.
bool aes_ecb_encrypt(
    unsigned char* const plaintext,
    const int plaintext_size,
    unsigned char* ciphertext,
    const unsigned char* const key
);

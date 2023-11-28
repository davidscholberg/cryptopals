#pragma once

#include <stdbool.h>

// Prepends "comment1=cooking%20MCs;userdata=" and appends
// ";comment2=%20like%20a%20pound%20of%20bacon" to the plaintext input, pkcs7 pads the whole thing,
// and then encrypts this under an unknown key and IV via AES CBC. The given ciphertext buffer must
// already have the needed amount of space, which you can determine with the aes_cbc_oracle_size
// function. Returns true on success, false on encryption error.
bool aes_cbc_oracle(
    const unsigned char* const plaintext,
    const int plaintext_size,
    unsigned char* const ciphertext
);

// Decrypt the given string under the secret key used to encrypt it with aes_cbc_oracle. The given
// plaintext buffer must have at least as much space allocated as the ciphertext.
bool aes_cbc_oracle_decrypt(
    unsigned char* const ciphertext,
    const int ciphertext_size,
    unsigned char* const plaintext
);

// Returns the amount of space needed to hold the output of aes_cbc_oracle with the given input
// size.
int aes_cbc_oracle_size(const int plaintext_size);

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

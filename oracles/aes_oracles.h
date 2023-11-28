#pragma once

#include <stdbool.h>

// Function type for functions that take an input buffer, optionally prepend or append some unknown
// text to it, pkcs7 pad this data to an unknown block size, and then encrypt the whole thing using
// aes with an unknown secret key.
typedef bool (*aes_oracle_fn)(const unsigned char* const, const int, unsigned char* const);

// Function type for functions that return the size needed to hold the output of the associated aes
// oracle function given the input size.
typedef int (*aes_oracle_size_fn)(const int);

// Take the given plaintext, prepend and append unknown strings to it, pkcs7 pad the result, and
// encrypt the whole thing with an unknown key using either ECB mode or CBC mode (chosen based on
// unknown criteria). Returns true on success or false if there was an encryption error. The given
// ciphertext buffer must already have the necessary space allocated for the added bytes and
// padding; use the aes_ecb_cbc_oracle_max_size_needed macro to get the maximum amount of space
// needed.
bool aes_ecb_or_cbc_oracle(
    const unsigned char* const plaintext,
    const int plaintext_size,
    unsigned char* const ciphertext
);

// Returns the amount of space needed to hold the output of aes_ecb_or_cbc_oracle with the given
// input size.
int aes_ecb_or_cbc_oracle_size(const int plaintext_size);

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

// Take the given plaintext, prepend and append two constant but unknown strings to it, pkcs7 pad
// it, and encrypt the whole thing via AES ECB with a constant but unknown key. The given ciphertext
// buffer must already have the needed amount of space, which you can determine with the
// aes_ecb_with_prefix_oracle_size function. The given plaintext_size should not include the extra
// space needed for the unknown strings.
bool aes_ecb_with_prefix_oracle(
    const unsigned char* const plaintext,
    const int plaintext_size,
    unsigned char* const ciphertext
);

// Returns the amount of space needed to hold the output of aes_ecb_with_prefix_oracle with the
// given input size.
int aes_ecb_with_prefix_oracle_size(const int plaintext_size);

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

// Decrypt the given profile under the secret key used to encrypt it. The given plaintext buffer
// must have at least as much space allocated as the ciphertext. This function exists merely to
// verify the result of breaking encrypted_profile_oracle.
bool encrypted_profile_decrypt(
    unsigned char* const ciphertext,
    const int ciphertext_size,
    unsigned char* const plaintext
);

// Take the given plaintext and encrypt it via AES CTR with an unknown key and IV. If ciphertext is
// null, encrypt in place.
void aes_ctr_unknown_key_oracle(
    unsigned char* const plaintext,
    const int plaintext_size,
    unsigned char* ciphertext
);

// Take the ciphertext and replace the section of it starting with offset and being of plaintext
// size with the given plaintext, encrypting the plaintext with the same unknown key as if it was a
// part of the original plaintext. The given ciphertext must have enough space allocated to
// accomodate plaintext size plus the offset.
void aes_ctr_unknown_key_edit_oracle(
    unsigned char* const ciphertext,
    unsigned char* const plaintext,
    const int plaintext_size,
    const int offset
);

// Takes the given email address, formats it into a profile string, and encrypts the profile string
// under a consistent secret key using AES ECB with a block size of 16. The given ciphertext buffer
// must already have the needed amount of space, which can be determined via the
// encrypted_profile_oracle_size function.
bool encrypted_profile_oracle(
    const unsigned char* const email,
    const int email_size,
    unsigned char* const ciphertext
);

// Returns the amount of space needed to hold the encrypted profile given the email address size.
int encrypted_profile_oracle_size(const int email_size);

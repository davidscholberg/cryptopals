#pragma once

// Enum used to indicate which block cipher mode to use with the encrypted profile functions.
typedef enum block_cipher_mode {
    aes_cbc,
    aes_ctr,
} block_cipher_mode;

// Prepends "comment1=cooking%20MCs;userdata=" and appends
// ";comment2=%20like%20a%20pound%20of%20bacon" to the plaintext input, pkcs7 pads the whole thing
// if CBC mode is set, and then encrypts this under an unknown key and IV via AES CBC or CTR. The
// given ciphertext buffer must already have the needed amount of space, which you can determine
// with the user_data_oracle_size function. Returns true on success, false on encryption error.
bool user_data_oracle(
    const unsigned char* const plaintext,
    const int plaintext_size,
    unsigned char* const ciphertext
);

// Decrypt the given string under the secret key used to encrypt it with user_data_oracle. The given
// plaintext buffer must have at least as much space allocated as the ciphertext.
bool user_data_oracle_decrypt(
    unsigned char* const ciphertext,
    const int ciphertext_size,
    unsigned char* const plaintext
);

// Set subsequent calls of the user data oracle to use CBC mode.
void user_data_oracle_set_cbc_mode(void);

// Set subsequent calls of the user data oracle to use CTR mode.
void user_data_oracle_set_ctr_mode(void);

// Returns the amount of space needed to hold the output of user_data_oracle with the given input
// size.
int user_data_oracle_size(const int plaintext_size);

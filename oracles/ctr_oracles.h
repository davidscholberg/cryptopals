#pragma once

#include <stdbool.h>

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

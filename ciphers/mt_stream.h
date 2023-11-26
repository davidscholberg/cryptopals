#pragma once

#include <stdint.h>

// Decrypt the given ciphertext using a Mersenne Twister PRNG seeded with the key. If plaintext is
// null, decryption happens in-place. If not null, the given plaintext must already have the needed
// space allocated.
void mt_stream_decrypt(
    unsigned char* const ciphertext,
    const int ciphertext_size,
    unsigned char* plaintext,
    const uint16_t key
);

// Encrypt the given plaintext using a Mersenne Twister PRNG seeded with the key. If ciphertext is
// null, encryption happens in-place. If not null, the given ciphertext must already have the needed
// space allocated.
void mt_stream_encrypt(
    unsigned char* const plaintext,
    const int plaintext_size,
    unsigned char* ciphertext,
    const uint16_t key
);

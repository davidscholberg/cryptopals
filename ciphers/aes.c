#include <stdbool.h>
#include <stdint.h>
#include <string.h>

#include "tiny-aes.h"

#include "aes.h"
#include "xor.h"

// This should almost certainly be defined in a more centralized place.
#define min(x, y) (((x) < (y)) ? (x) : (y))

bool aes_cbc_decrypt(
    unsigned char* const ciphertext,
    const int ciphertext_size,
    unsigned char* plaintext,
    const unsigned char* const iv,
    const unsigned char* const key
) {
    const int block_count = ciphertext_size / aes_block_size;
    if (block_count == 0) {
        return false;
    }

    if (plaintext) {
        memcpy(plaintext, ciphertext, ciphertext_size);
    } else {
        plaintext = ciphertext;
    }

    struct AES_ctx aes_ecb_context;
    AES_init_ctx(&aes_ecb_context, key);

    for (int i = block_count - 1; i > 0; i--) {
        unsigned char* const current_block = plaintext + (i * aes_block_size);
        const unsigned char* const previous_block = current_block - aes_block_size;

        AES_ECB_decrypt(&aes_ecb_context, current_block);
        xor_bytes(current_block, previous_block, current_block, aes_block_size);
    }

    AES_ECB_decrypt(&aes_ecb_context, plaintext);
    xor_bytes(plaintext, iv, plaintext, aes_block_size);

    return true;
}

bool aes_cbc_encrypt(
    unsigned char* const plaintext,
    const int plaintext_size,
    unsigned char* ciphertext,
    const unsigned char* const iv,
    const unsigned char* const key
) {
    const int block_count = plaintext_size / aes_block_size;
    if (block_count == 0) {
        return false;
    }

    if (ciphertext) {
        memcpy(ciphertext, plaintext, plaintext_size);
    } else {
        ciphertext = plaintext;
    }

    struct AES_ctx aes_ecb_context;
    AES_init_ctx(&aes_ecb_context, key);

    xor_bytes(ciphertext, iv, ciphertext, aes_block_size);
    AES_ECB_encrypt(&aes_ecb_context, ciphertext);

    for (int i = 1; i < block_count; i++) {
        unsigned char* const current_block = ciphertext + (i * aes_block_size);
        const unsigned char* const previous_block = current_block - aes_block_size;

        xor_bytes(current_block, previous_block, current_block, aes_block_size);
        AES_ECB_encrypt(&aes_ecb_context, current_block);
    }

    return true;
}

void aes_ctr_decrypt(
    unsigned char* const ciphertext,
    const int ciphertext_size,
    unsigned char* plaintext,
    const unsigned char* const iv,
    const unsigned char* const key,
    const int offset
) {
    // CTR mode performs identical steps in encryption and decryption, so we merely pass along the
    // args to the encrypt function.
    aes_ctr_encrypt(ciphertext, ciphertext_size, plaintext, iv, key, offset);
}

void aes_ctr_encrypt(
    unsigned char* const plaintext,
    const int plaintext_size,
    unsigned char* ciphertext,
    const unsigned char* const iv,
    const unsigned char* const key,
    const int offset
) {
    if (!ciphertext) {
        ciphertext = plaintext;
    }

    unsigned char counter_block[aes_block_size];
    memcpy(counter_block, iv, aes_block_size);
    int64_t* counter = (int64_t*)(counter_block + (aes_block_size / 2));
    unsigned char keystream[aes_block_size];

    // Burn the counter to reach the block where the given offset is.
    // This is the block number that the offset resides in.
    const int offset_block = (offset / aes_block_size);
    (*counter) += offset_block;

    // This is the starting index of the offset block.
    const int offset_block_start = offset_block * aes_block_size;
    // This is the offset within the offset block.
    int block_offset = offset % aes_block_size;

    struct AES_ctx aes_ecb_context;
    AES_init_ctx(&aes_ecb_context, key);

    for (int i = offset_block_start; i < plaintext_size; i += aes_block_size) {
        memcpy(keystream, counter_block, aes_block_size);
        AES_ECB_encrypt(&aes_ecb_context, keystream);

        const int buffer_offset = i + block_offset;

        xor_bytes(
            keystream + block_offset,
            plaintext + buffer_offset,
            ciphertext + buffer_offset,
            min(aes_block_size, plaintext_size - buffer_offset)
        );

        (*counter)++;

        // block_offset should only ever be non-zero on the first iteration
        block_offset = 0;
    }
}

bool aes_ecb_decrypt(
    unsigned char* const ciphertext,
    const int ciphertext_size,
    unsigned char* plaintext,
    const unsigned char* const key
) {
    const int block_count = ciphertext_size / aes_block_size;
    if (block_count == 0) {
        return false;
    }

    if (plaintext) {
        memcpy(plaintext, ciphertext, ciphertext_size);
    } else {
        plaintext = ciphertext;
    }

    struct AES_ctx aes_ecb_context;
    AES_init_ctx(&aes_ecb_context, key);
    for (int i = 0; i < block_count; i++) {
        AES_ECB_decrypt(&aes_ecb_context, plaintext + (i * aes_block_size));
    }

    return true;
}

bool aes_ecb_encrypt(
    unsigned char* const plaintext,
    const int plaintext_size,
    unsigned char* ciphertext,
    const unsigned char* const key
) {
    const int block_count = plaintext_size / aes_block_size;
    if (block_count == 0) {
        return false;
    }

    if (ciphertext) {
        memcpy(ciphertext, plaintext, plaintext_size);
    } else {
        ciphertext = plaintext;
    }

    struct AES_ctx aes_ecb_context;
    AES_init_ctx(&aes_ecb_context, key);
    for (int i = 0; i < block_count; i++) {
        AES_ECB_encrypt(&aes_ecb_context, ciphertext + (i * aes_block_size));
    }

    return true;
}

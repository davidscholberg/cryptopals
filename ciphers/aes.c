#include <stdbool.h>
#include <string.h>

#include "tiny-aes.h"

#include "aes.h"
#include "xor.h"

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

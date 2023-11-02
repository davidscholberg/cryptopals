#include <stdbool.h>
#include <string.h>

#include "aes.h"
#include "aes_cbc.h"
#include "xor.h"

bool aes_cbc_decrypt(
    const unsigned char* const ciphertext,
    const int ciphertext_size,
    unsigned char* const plaintext,
    const unsigned char* const iv,
    const unsigned char* const key
) {
    const int block_count = ciphertext_size / aes_block_size;
    if (block_count == 0) {
        return false;
    }

    memcpy(plaintext, ciphertext, ciphertext_size);

    struct AES_ctx aes_ecb_context;
    AES_init_ctx(&aes_ecb_context, (const unsigned char* const)key);

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

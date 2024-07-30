#include <limits.h>
#include <stdbool.h>
#include <string.h>

#include "break_cbc.h"

bool break_cbc_padding_oracle(
    padding_oracle_fn padding_oracle,
    const unsigned char* const ciphertext,
    const int ciphertext_size,
    const unsigned char* const iv,
    const int iv_size,
    unsigned char* const plaintext
) {
    const int block_size = iv_size;
    const int block_count = ciphertext_size / block_size;
    const int tampered_ciphertext_size = block_size * 2;
    unsigned char tampered_ciphertext[tampered_ciphertext_size];
    unsigned char* const tamper_block = tampered_ciphertext;
    unsigned char pre_xor_plaintext[block_size];
    bool padding_is_valid = false;
    const unsigned char* untampered_block = NULL;

    for (int block_index = block_count - 2; block_index >= -1; block_index--) {
        if (block_index > -1) {
            untampered_block = ciphertext + (block_index * block_size);
            memcpy(tampered_ciphertext, untampered_block, tampered_ciphertext_size);
        } else {
            untampered_block = iv;
            memcpy(tampered_ciphertext, untampered_block, block_size);
            memcpy(tampered_ciphertext + block_size, ciphertext, block_size);
        }

        for (int byte_index = block_size - 1; byte_index >= 0; byte_index--) {
            // Determine tamper byte
            for (int byte_value = 0; byte_value <= UCHAR_MAX; byte_value++) {
                tamper_block[byte_index] = byte_value;
                if (!padding_oracle(
                        tampered_ciphertext,
                        tampered_ciphertext_size,
                        iv,
                        iv_size,
                        &padding_is_valid
                    )) {
                    return false;
                }

                if (padding_is_valid) {
                    break;
                }
            }

            // Determine actual padding byte
            int padding_byte = block_size - byte_index;
            if (byte_index == block_size - 1) {
                padding_byte = block_size;
                unsigned char original_tamper_byte = 0;
                for (int i = block_size - 2; i >= 0; i--) {
                    original_tamper_byte = tamper_block[i];
                    tamper_block[i] = (tamper_block[i] + 1) % (UCHAR_MAX + 1);

                    if (!padding_oracle(
                            tampered_ciphertext,
                            tampered_ciphertext_size,
                            iv,
                            iv_size,
                            &padding_is_valid
                        )) {
                        return false;
                    }

                    tamper_block[i] = original_tamper_byte;

                    if (padding_is_valid) {
                        padding_byte = block_size - 1 - i;
                        break;
                    }
                }
            }

            // Write decrypted byte to plaintext.
            pre_xor_plaintext[byte_index] = tamper_block[byte_index] ^ padding_byte;
            plaintext[((block_index + 1) * block_size) + byte_index] =
                untampered_block[byte_index] ^ pre_xor_plaintext[byte_index];

            // Tee up tamper_block for next byte.
            if (byte_index > 0) {
                const int next_padding_byte = padding_byte + 1;
                for (int i = block_size - 1; i > block_size - next_padding_byte; i--) {
                    tamper_block[i] = next_padding_byte ^ pre_xor_plaintext[i];
                }
            }
        }
    }

    return true;
}

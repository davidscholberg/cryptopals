#include <stdlib.h>
#include <string.h>

#include "ciphers/aes.h"
#include "oracles.h"
#include "pkcs7_pad.h"
#include "random.h"

int aes_ecb_cbc_oracle(
    const unsigned char* const plaintext,
    const int plaintext_size,
    unsigned char* const ciphertext,
    cipher_mode* const cipher_mode_used
) {
    initialize_rand();
    const int prepend_size =
        (rand() % (aes_ecb_cbc_oracle_max_prepend - aes_ecb_cbc_oracle_min_prepend + 1)) +
        aes_ecb_cbc_oracle_min_prepend;
    const int append_size =
        (rand() % (aes_ecb_cbc_oracle_max_append - aes_ecb_cbc_oracle_min_append + 1)) +
        aes_ecb_cbc_oracle_min_append;
    memcpy(ciphertext + prepend_size, plaintext, plaintext_size);
    int total_buffer_size = prepend_size + plaintext_size + append_size;

    pkcs7_pad(ciphertext, NULL, total_buffer_size, aes_block_size);
    total_buffer_size += pkcs7_padding_needed(total_buffer_size, aes_block_size);

    unsigned char key[aes_block_size];
    random_buffer(key, aes_block_size);

    if (rand() % 2) {
        // we're doing ecb
        if (cipher_mode_used) {
            *cipher_mode_used = ecb;
        }

        if (!aes_ecb_encrypt(ciphertext, total_buffer_size, NULL, key)) {
            return -1;
        }
    } else {
        // we're doing cbc
        if (cipher_mode_used) {
            *cipher_mode_used = cbc;
        }

        unsigned char iv[aes_block_size];
        random_buffer(iv, aes_block_size);

        if (!aes_cbc_encrypt(ciphertext, total_buffer_size, NULL, iv, key)) {
            return -1;
        }
    }

    return total_buffer_size;
}

// Secret text that gets appended to the plaintext input of aes_ecb_oracle. Challenge 12 calls for
// this string to be initially base64 encoded, but I don't think that pre-decoding it has any
// bearing on successfully completing the challenge.
static const char* const aes_ecb_oracle_secret_text =
    "Rollin' in my 5.0\nWith my rag-top down so my hair can blow\nThe girlies on standby waving "
    "just to say hi\nDid you stop? No, I just drove by\n";

// Secret key used by the aes_ecb_oracle.
static const char* const aes_ecb_oracle_secret_key = "iceicebabyiceice";

bool aes_ecb_oracle(
    const unsigned char* const plaintext,
    const int plaintext_size,
    unsigned char* const ciphertext
) {
    memcpy(ciphertext, plaintext, plaintext_size);

    const int sectret_text_size = strlen(aes_ecb_oracle_secret_text);
    memcpy(ciphertext + plaintext_size, aes_ecb_oracle_secret_text, sectret_text_size);

    const int total_data_size = plaintext_size + sectret_text_size;
    pkcs7_pad(ciphertext, NULL, total_data_size, aes_block_size);

    const int padded_plaintext_size = aes_ecb_oracle_size(plaintext_size);
    return aes_ecb_encrypt(
        ciphertext,
        padded_plaintext_size,
        NULL,
        (const unsigned char* const)aes_ecb_oracle_secret_key
    );
}

int aes_ecb_oracle_size(const int plaintext_size) {
    const int total_data_size = plaintext_size + strlen(aes_ecb_oracle_secret_text);
    return total_data_size + pkcs7_padding_needed(total_data_size, aes_block_size);
}
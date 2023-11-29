#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "ciphers/aes.h"
#include "user_data_oracle.h"
#include "utility/pkcs7_pad.h"

static block_cipher_mode current_mode = aes_cbc;

static const char* const user_data_oracle_iv = "fire fire adult.";
static const char* const user_data_oracle_key = "cooking mc bacon";
static const char* const user_data_oracle_prefix = "comment1=cooking%20MCs;userdata=";
static const char* const user_data_oracle_suffix = ";comment2=%20like%20a%20pound%20of%20bacon";

bool user_data_oracle(
    const unsigned char* const plaintext,
    const int plaintext_size,
    unsigned char* const ciphertext
) {
    const int prefix_size = strlen(user_data_oracle_prefix);
    memcpy(ciphertext, user_data_oracle_prefix, prefix_size);
    memcpy(ciphertext + prefix_size, plaintext, plaintext_size);
    const int suffix_size = strlen(user_data_oracle_suffix);
    memcpy(ciphertext + prefix_size + plaintext_size, user_data_oracle_suffix, suffix_size);

    int data_size = prefix_size + plaintext_size + suffix_size;

    if (current_mode == aes_cbc) {
        pkcs7_pad(ciphertext, NULL, data_size, aes_block_size);
        data_size += pkcs7_padding_needed(data_size, aes_block_size);

        return aes_cbc_encrypt(
            ciphertext,
            data_size,
            NULL,
            (const unsigned char* const)user_data_oracle_iv,
            (const unsigned char* const)user_data_oracle_key
        );
    }

    if (current_mode == aes_ctr) {
        aes_ctr_encrypt(
            ciphertext,
            data_size,
            NULL,
            (const unsigned char* const)user_data_oracle_iv,
            (const unsigned char* const)user_data_oracle_key,
            0
        );

        return true;
    }

    return false;
}

bool user_data_oracle_decrypt(
    unsigned char* const ciphertext,
    const int ciphertext_size,
    unsigned char* const plaintext
) {
    if (current_mode == aes_cbc) {
        return aes_cbc_decrypt(
            ciphertext,
            ciphertext_size,
            plaintext,
            (const unsigned char* const)user_data_oracle_iv,
            (const unsigned char* const)user_data_oracle_key
        );
    }

    if (current_mode == aes_ctr) {
        aes_ctr_decrypt(
            ciphertext,
            ciphertext_size,
            plaintext,
            (const unsigned char* const)user_data_oracle_iv,
            (const unsigned char* const)user_data_oracle_key,
            0
        );

        return true;
    }

    return false;
}

void user_data_oracle_set_cbc_mode(void) { current_mode = aes_cbc; }

void user_data_oracle_set_ctr_mode(void) { current_mode = aes_ctr; }

int user_data_oracle_size(const int plaintext_size) {
    int data_size =
        strlen(user_data_oracle_prefix) + plaintext_size + strlen(user_data_oracle_suffix);

    if (current_mode == aes_cbc) {
        data_size += pkcs7_padding_needed(data_size, aes_block_size);
    }

    return data_size;
}

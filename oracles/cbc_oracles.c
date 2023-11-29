#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "ciphers/aes.h"
#include "utility/pkcs7_pad.h"

static const char* const aes_cbc_unknown_plaintext_oracle_plaintext =
    "With the bass kicked in and the Vega's are pumpin'";
static const char* const aes_cbc_unknown_plaintext_oracle_key = "cymbal crazed af";

bool aes_cbc_unknown_plaintext_oracle(unsigned char* const ciphertext, unsigned char* const iv) {
    static const char* const iv_str = "!chocolate lava!";
    memcpy(iv, iv_str, aes_block_size);

    const int plaintext_size = strlen(aes_cbc_unknown_plaintext_oracle_plaintext);
    memcpy(ciphertext, aes_cbc_unknown_plaintext_oracle_plaintext, plaintext_size);

    pkcs7_pad(ciphertext, NULL, plaintext_size, aes_block_size);
    const int padded_data_size =
        plaintext_size + pkcs7_padding_needed(plaintext_size, aes_block_size);

    return aes_cbc_encrypt(
        ciphertext,
        padded_data_size,
        NULL,
        (const unsigned char* const)iv_str,
        (const unsigned char* const)aes_cbc_unknown_plaintext_oracle_key
    );
}

int aes_cbc_unknown_plaintext_oracle_iv_size(void) { return aes_block_size; }

int aes_cbc_unknown_plaintext_oracle_size(void) {
    const int data_size = strlen(aes_cbc_unknown_plaintext_oracle_plaintext);
    return data_size + pkcs7_padding_needed(data_size, aes_block_size);
}

bool aes_cbc_unknown_plaintext_oracle_verify_padding(
    unsigned char* const ciphertext,
    const int ciphertext_size,
    const unsigned char* const iv,
    const int iv_size,
    bool* const padding_is_valid
) {
    unsigned char plaintext[ciphertext_size];

    if (!aes_cbc_decrypt(
            ciphertext,
            ciphertext_size,
            plaintext,
            iv,
            (const unsigned char* const)aes_cbc_unknown_plaintext_oracle_key
        )) {
        return false;
    }

    *padding_is_valid = pkcs7_validate(plaintext, ciphertext_size, iv_size);
    return true;
}

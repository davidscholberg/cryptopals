#include "ciphers/aes.h"
#include "utility/pkcs7_pad.h"

static const unsigned char aes_ctr_unknown_key_oracle_iv[aes_block_size] = {0};
static const char* const aes_ctr_unknown_key_oracle_key = "vanilla ice baby";

void aes_ctr_unknown_key_oracle(
    unsigned char* const plaintext,
    const int plaintext_size,
    unsigned char* ciphertext
) {
    aes_ctr_encrypt(
        plaintext,
        plaintext_size,
        ciphertext,
        aes_ctr_unknown_key_oracle_iv,
        (const unsigned char* const)aes_ctr_unknown_key_oracle_key,
        0
    );
}

void aes_ctr_unknown_key_edit_oracle(
    unsigned char* const ciphertext,
    unsigned char* const plaintext,
    const int plaintext_size,
    const int offset
) {
    aes_ctr_encrypt(
        plaintext,
        plaintext_size,
        ciphertext,
        aes_ctr_unknown_key_oracle_iv,
        (const unsigned char* const)aes_ctr_unknown_key_oracle_key,
        offset
    );
}

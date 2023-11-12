#include <limits.h>
#include <stdbool.h>
#include <stdio.h>

#include "uncrypt/break_cbc.h"
#include "utility/oracles.h"
#include "utility/pkcs7_pad.h"

// Challenge 17: Decrypt the CBC-encrypted text via padding oracle attack.
bool s17(char* const out_buffer, const int out_buffer_size) {
    const int ciphertext_size = aes_cbc_unknown_plaintext_oracle_size();
    if (ciphertext_size > out_buffer_size + 1) {
        return false;
    }

    unsigned char ciphertext[ciphertext_size];
    const int iv_size = aes_cbc_unknown_plaintext_oracle_iv_size();
    unsigned char iv[iv_size];
    if (!aes_cbc_unknown_plaintext_oracle(ciphertext, iv)) {
        return false;
    }

    if (!break_cbc_padding_oracle(
            aes_cbc_unknown_plaintext_oracle_verify_padding,
            ciphertext,
            ciphertext_size,
            iv,
            iv_size,
            (unsigned char* const)out_buffer
        )) {
        return false;
    }

    out_buffer[ciphertext_size - pkcs7_padding_size(out_buffer, ciphertext_size)] = 0;

    return true;
}

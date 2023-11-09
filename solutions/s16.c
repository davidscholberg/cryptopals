#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "analysis/oracle_info.h"
#include "utility/oracles.h"

#define prefix_size 32

// Challenge 16: Do a bit flipping attack to generate an admin string from the CBC ciphertext.
bool s16(char* const out_buffer, const int out_buffer_size) {
    const char* const input_string = "a:admin<true";
    const int input_string_size = strlen(input_string);
    const int ciphertext_size = aes_cbc_oracle_size(input_string_size);
    unsigned char ciphertext[ciphertext_size];
    if (!aes_cbc_oracle((const unsigned char* const)input_string, input_string_size, ciphertext)) {
        return false;
    }

    int block_size = 0;
    if (!oracle_info(aes_cbc_oracle, aes_cbc_oracle_size, &block_size, NULL, NULL, NULL, NULL)) {
        return false;
    }
    const int colon_offset = strchr(input_string, ':') - input_string + prefix_size - block_size;
    const int lt_offset = strchr(input_string, '<') - input_string + prefix_size - block_size;
    ciphertext[colon_offset] ^= 0x1;
    ciphertext[lt_offset] ^= 0x1;

    unsigned char hax0red_plaintext[ciphertext_size];
    if (!aes_cbc_oracle_decrypt(ciphertext, ciphertext_size, hax0red_plaintext)) {
        return false;
    }

    if (strstr((const char*)hax0red_plaintext, ";admin=true;")) {
        strncpy(out_buffer, "successfully flipped bits to get admin string", out_buffer_size);
    } else {
        strncpy(out_buffer, "couldn't find admin string", out_buffer_size);
    }

    return true;
}

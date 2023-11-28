#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ciphers/aes.h"
#include "ciphers/xor.h"
#include "codecs/base64.h"
#include "oracles/ctr_oracles.h"
#include "utility/files.h"

#define known_plaintext_byte 0

// Challenge 25: Encrypt the given plaintext with the AES CTR unknown key oracle, and then use the
// AES CTR edit oracle to determine the keystream that the oracle used to encrypt the ciphertext,
// and decrypt the ciphertext with this keystream.
bool s25(char* const out_buffer, const int out_buffer_size) {
    char* base64_string = file_to_string("s25_base64_string.txt");
    if (!base64_string) {
        return false;
    }

    int ciphertext_size = 0;
    if (!base64_to_bytes_size(base64_string, &ciphertext_size)) {
        free(base64_string);
        return false;
    }
    if (ciphertext_size % aes_block_size != 0 || ciphertext_size + 1 > out_buffer_size) {
        free(base64_string);
        return false;
    }
    unsigned char ciphertext[ciphertext_size];
    if (!base64_to_bytes(base64_string, ciphertext, ciphertext_size)) {
        free(base64_string);
        return false;
    }
    free(base64_string);

    const char* const key = "YELLOW SUBMARINE";
    if (!aes_ecb_decrypt(ciphertext, ciphertext_size, NULL, (const unsigned char* const)key)) {
        return false;
    }

    aes_ctr_unknown_key_oracle(ciphertext, ciphertext_size, NULL);

    unsigned char known_plaintext[ciphertext_size];
    unsigned char edited_ciphertext[ciphertext_size];
    for (int i = 0; i < ciphertext_size; i++) {
        known_plaintext[i] = known_plaintext_byte;
        edited_ciphertext[i] = ciphertext[i];
    }

    aes_ctr_unknown_key_edit_oracle(edited_ciphertext, known_plaintext, ciphertext_size, 0);

    unsigned char keystream[ciphertext_size];
    for (int i = 0; i < ciphertext_size; i++) {
        keystream[i] = known_plaintext_byte ^ edited_ciphertext[i];
    }

    xor_bytes(ciphertext, keystream, (unsigned char* const)out_buffer, ciphertext_size);
    out_buffer[ciphertext_size] = 0;

    // cap output at end of first line
    char* const newline = strchr(out_buffer, '\n');
    if (newline) {
        *newline = 0;
    }

    return true;
}

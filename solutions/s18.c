#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "ciphers/aes.h"
#include "codecs/base64.h"

// Challenge 18: Decrypt the given string via AES CTR.
bool s18(char* const out_buffer, const int out_buffer_size) {
    const char* const base64_str =
        "L77na/nrFsKvynd6HzOoG7GHTLXsTVu9qvY/2syLXzhPweyyMTJULu/6/kXX0KSvoOLSFQ==";
    int input_bytes_size = 0;
    if (!base64_to_bytes_size(base64_str, &input_bytes_size)) {
        return false;
    }
    if (input_bytes_size > out_buffer_size + 1) {
        return false;
    }
    if (!base64_to_bytes(base64_str, (unsigned char* const)out_buffer, input_bytes_size)) {
        return false;
    }

    const char* const key = "YELLOW SUBMARINE";
    const unsigned char iv[aes_block_size] = {0};
    aes_ctr_decrypt(
        (unsigned char* const)out_buffer,
        input_bytes_size,
        NULL,
        iv,
        (const unsigned char* const)key
    );
    out_buffer[input_bytes_size] = 0;

    return true;
}

#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "gcrypt.h"

#include "codecs/base64.h"
#include "resources/s07_base64_string.h"

// Challenge 7: Decrypt the base64-encoded string using AES in ECB mode with key "YELLOW SUBMARINE".
bool s07(char* const out_buffer, const int out_buffer_size) {
    const char* const key = "YELLOW SUBMARINE";
    int input_bytes_size = 0;
    if (!base64_to_bytes_size(s07_base64_string, &input_bytes_size)) {
        return false;
    }
    unsigned char input_bytes[input_bytes_size];
    if (!base64_to_bytes(s07_base64_string, input_bytes, input_bytes_size)) {
        return false;
    }

    // initialize gcrypt
    gcry_check_version(0);
    gcry_control(GCRYCTL_DISABLE_SECMEM, 0);
    gcry_control(GCRYCTL_INITIALIZATION_FINISHED, 0);

    gcry_cipher_hd_t aes_ecb_handle;
    if (gcry_cipher_open(&aes_ecb_handle, GCRY_CIPHER_AES128, GCRY_CIPHER_MODE_ECB, 0)) {
        return false;
    }
    if (gcry_cipher_setkey(aes_ecb_handle, key, strlen(key))) {
        gcry_cipher_close(aes_ecb_handle);
        return false;
    }
    if (gcry_cipher_decrypt(
            aes_ecb_handle,
            out_buffer,
            out_buffer_size,
            input_bytes,
            input_bytes_size
        )) {
        gcry_cipher_close(aes_ecb_handle);
        return false;
    }
    gcry_cipher_close(aes_ecb_handle);

    out_buffer[input_bytes_size] = 0;

    // cap output at end of first line
    char* const newline = strchr(out_buffer, '\n');
    if (newline) {
        *newline = 0;
    }

    return true;
}

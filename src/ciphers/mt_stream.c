#include <limits.h>
#include <stdint.h>

#include "mt_stream.h"
#include "utility/mersenne_twister.h"

void mt_stream_decrypt(
    unsigned char* const ciphertext,
    const int ciphertext_size,
    unsigned char* plaintext,
    const uint16_t key
) {
    // With this cipher, encrypting and decrypting are the exact same process, so we just pass the
    // args along to the encrypt function.
    mt_stream_encrypt(ciphertext, ciphertext_size, plaintext, key);
}

void mt_stream_encrypt(
    unsigned char* const plaintext,
    const int plaintext_size,
    unsigned char* ciphertext,
    const uint16_t key
) {
    if (!ciphertext) {
        ciphertext = plaintext;
    }

    mersenne_twister mt_state;
    mersenne_twister_seed(&mt_state, key);

    for (int i = 0; i < plaintext_size; i++) {
        ciphertext[i] = plaintext[i] ^ (mersenne_twister_next(&mt_state) % (UCHAR_MAX + 1));
    }
}

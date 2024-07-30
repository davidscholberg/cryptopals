#include <string.h>

#include "ciphers/mt_stream.h"
#include "utility/mersenne_twister.h"

unsigned int mersenne_twister_time_delay_oracle(int* const elapsed_time) {
    mersenne_twister mt_state;
    mersenne_twister_seed(&mt_state, 212);
    *elapsed_time = 935;
    return mersenne_twister_next(&mt_state);
}

static const char* const mt_stream_random_prefix_oracle_prefix =
    "I'm on a roll, it's time to go solo";

void mt_stream_random_prefix_oracle(
    const unsigned char* const plaintext,
    const int plaintext_size,
    unsigned char* const ciphertext
) {
    const int prefix_size = strlen(mt_stream_random_prefix_oracle_prefix);
    memcpy(ciphertext, mt_stream_random_prefix_oracle_prefix, prefix_size);
    memcpy(ciphertext + prefix_size, plaintext, plaintext_size);
    const int total_plaintext_size = prefix_size + plaintext_size;

    static const unsigned short key = 5649;
    mt_stream_encrypt(ciphertext, total_plaintext_size, NULL, key);
}

int mt_stream_random_prefix_oracle_size(const int plaintext_size) {
    return strlen(mt_stream_random_prefix_oracle_prefix) + plaintext_size;
}

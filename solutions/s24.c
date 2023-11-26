#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "oracles/mersenne_twister_oracles.h"
#include "uncrypt/break_mersenne_twister.h"

#define rand_n_cap 100
#define rand_n_count 20
#define rand_n_max_digits 2
#define rand_n_seed 824824

// Challenge 24: Given an mt stream oracle that encrypts a known plaintext with an unknown seed,
// determine the seed using only the ciphertext. Note that this challenge has a second part which
// from what I can tell is almost identical to challenge 22, so I chose not to do it. Simply deal
// with it.
bool s24(char* const out_buffer, const int out_buffer_size) {
    const char* const plaintext = "AAAAAAAAAAAAAA";
    const int plaintext_size = strlen(plaintext);
    const int ciphertext_size = mt_stream_random_prefix_oracle_size(plaintext_size);
    unsigned char ciphertext[ciphertext_size];
    mt_stream_random_prefix_oracle(
        (const unsigned char* const)plaintext,
        plaintext_size,
        ciphertext
    );

    const unsigned short seed =
        crack_mt_stream_seed(ciphertext, ciphertext_size, 'A', plaintext_size);

    int ret = snprintf(out_buffer, out_buffer_size, "%hu", seed);
    if (ret <= 0 || ret >= out_buffer_size) {
        return false;
    }

    return true;
}

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "uncrypt/break_mersenne_twister.h"
#include "utility/mersenne_twister.h"

#define rand_n_cap 100
#define rand_n_count 20
#define rand_n_max_digits 2
#define rand_n_seed 824824

// Challenge 23: Reverse engineer the state of a Mersenne Twister PRNG given only its output, such
// that subsequent values of the reverse engineered PRNG are identical to the original PRNG.
bool s23(char* const out_buffer, const int out_buffer_size) {
    const char* const rand_n_separator = ", ";
    const int rand_n_separator_len = strlen(rand_n_separator);

    const int max_string_space =
        (rand_n_count * rand_n_max_digits) + ((rand_n_count - 1) * rand_n_separator_len) + 1;

    if (out_buffer_size < max_string_space) {
        return false;
    }

    mersenne_twister original_mt;
    mersenne_twister_seed(&original_mt, rand_n_seed);

    unsigned int original_mt_output[mersenne_twister_n];
    for (int i = 0; i < (int)mersenne_twister_n; i++) {
        original_mt_output[i] = mersenne_twister_next(&original_mt);
    }

    mersenne_twister clone_mt;
    mersenne_twister_clone(original_mt_output, &clone_mt);

    char* out_buffer_ptr = out_buffer;
    for (int i = 0; i < rand_n_count; i++) {
        const unsigned int rand_n = mersenne_twister_next(&clone_mt) % rand_n_cap;

        int chars = snprintf(out_buffer_ptr, rand_n_max_digits + 1, "%u", rand_n);
        if (chars <= 0 || chars > rand_n_max_digits) {
            return false;
        }
        out_buffer_ptr += chars;

        if (i < rand_n_count - 1) {
            int chars = snprintf(out_buffer_ptr, rand_n_separator_len + 1, "%s", rand_n_separator);
            if (chars != rand_n_separator_len) {
                return false;
            }
            out_buffer_ptr += chars;
        }
    }

    return true;
}

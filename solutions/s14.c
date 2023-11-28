#include <limits.h>
#include <stdbool.h>
#include <stdio.h>

#include "oracles/ecb_oracles.h"
#include "uncrypt/break_ecb.h"

// Challenge 14: Decrypt the string that's being appended to the input of the encryption oracle.
bool s14(char* const out_buffer, const int out_buffer_size) {
    const int suffix_size = break_ecb(
        aes_ecb_with_prefix_oracle,
        aes_ecb_with_prefix_oracle_size,
        (unsigned char* const)out_buffer,
        out_buffer_size - 1
    );
    if (suffix_size == -1) {
        return false;
    }

    out_buffer[suffix_size] = 0;

    return true;
}

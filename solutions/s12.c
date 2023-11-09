#include <limits.h>
#include <stdbool.h>
#include <stdio.h>

#include "uncrypt/break_ecb.h"
#include "utility/oracles.h"

// Challenge 12: Decrypt the string that's being appended to the input of the encryption oracle.
bool s12(char* const out_buffer, const int out_buffer_size) {
    const int suffix_size = break_ecb(
        aes_ecb_oracle,
        aes_ecb_oracle_size,
        (unsigned char* const)out_buffer,
        out_buffer_size - 1
    );
    if (suffix_size == -1) {
        return false;
    }

    out_buffer[suffix_size] = 0;

    return true;
}

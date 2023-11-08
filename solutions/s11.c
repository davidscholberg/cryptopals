#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "analysis/oracle_info.h"
#include "utility/oracles.h"

#define passes 10

// Challenge 11: Create function that randomly encrypts with ECB or CBC and detect which mode it
// uses.
bool s11(char* const out_buffer, const int out_buffer_size) {
    int block_size = 0;
    bool is_using_ecb = false;
    bool passed = true;
    for (int i = 0; i < passes; i++) {
        if (!oracle_info(
                aes_ecb_or_cbc_oracle,
                aes_ecb_or_cbc_oracle_size,
                &block_size,
                NULL,
                &is_using_ecb,
                NULL,
                NULL
            )) {
            return false;
        }

        if (is_using_ecb == i % 2) {
            passed = false;
            break;
        }
    }

    if (passed) {
        strncpy(out_buffer, "guessed all cipher modes correctly", out_buffer_size);
    } else {
        strncpy(out_buffer, "incorrectly guessed cipher mode", out_buffer_size);
    }

    return true;
}

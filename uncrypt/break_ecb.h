#pragma once

#include "oracles/aes_oracles.h"

// Given the aes encryption oracle, if the oracle uses ECB, decrypt any suffix string added by the
// oracle and copy it to the output buffer. Returns the size of the suffix string (not including a
// null terminator, which is not written to the output buffer), or -1 on oracle error or if the
// oracle doesn't use ECB or if the output buffer size is too small for the output.
int break_ecb(
    aes_oracle_fn oracle,
    aes_oracle_size_fn oracle_size,
    unsigned char* const output_buffer,
    const int output_buffer_size
);

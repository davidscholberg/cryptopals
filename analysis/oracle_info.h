#pragma once

#include <stdbool.h>

#include "oracles/aes_oracles.h"

// Get some info about the given aes oracle function. All of the non-function pointer parameters may
// be null except block_size. If added_data_size or prefix_size is null, then suffix size will not
// be calculated. If is_using_ecb is null or set to false by this function, then prefix_size and
// suffix_size will not be calculated. Return true on success and false on oracle error.
//
// Note that determining if ECB is being used as well as determining prefix and suffix sizes only
// works reliably if none of the data added by the oracle includes a lot of consecutive repeating
// characters or null bytes.
bool aes_oracle_info(
    aes_oracle_fn oracle,
    aes_oracle_size_fn oracle_size,
    int* const block_size,
    int* const added_data_size,
    bool* const is_using_ecb,
    int* const prefix_size,
    int* const suffix_size
);

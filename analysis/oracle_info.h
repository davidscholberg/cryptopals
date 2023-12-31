#pragma once

#include <stdbool.h>

// Function type for functions that take an input buffer, optionally prepend or append some unknown
// text to it, pkcs7 pad this data to an unknown block size, and then encrypt the whole thing using
// aes with an unknown secret key.
typedef bool (*block_cipher_oracle_fn)(const unsigned char* const, const int, unsigned char* const);

// Function type for functions that return the size needed to hold the output of the associated aes
// oracle function given the input size.
typedef int (*block_cipher_oracle_size_fn)(const int);

// Get some info about the given block cipher oracle function. All of the non-function pointer
// parameters may be null except block_size. If added_data_size or prefix_size is null, then suffix
// size will not be calculated. If is_using_ecb is null or set to false by this function, then
// prefix_size and suffix_size will not be calculated. Return true on success and false on oracle
// error.
//
// Note that determining if ECB is being used as well as determining prefix and suffix sizes only
// works reliably if none of the data added by the oracle includes a lot of consecutive repeating
// characters or null bytes.
bool block_cipher_oracle_info(
    block_cipher_oracle_fn oracle,
    block_cipher_oracle_size_fn oracle_size,
    int* const block_size,
    int* const added_data_size,
    bool* const is_using_ecb,
    int* const prefix_size,
    int* const suffix_size
);

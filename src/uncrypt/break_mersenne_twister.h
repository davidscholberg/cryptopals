#pragma once

#include <stdint.h>

#include "utility/mersenne_twister.h"

// Given the ciphertext that was produced by an mt stream oracle seeded with an unknown 16-bit value
// and originally containing a known contiguous string of the given target plaintext byte and of
// target_size, determine what the unknown seed value was.
uint16_t crack_mt_stream_seed(
    const unsigned char* const ciphertext,
    const int ciphertext_size,
    const unsigned char target_plaintext_byte,
    const int target_size
);

// Take the given input of mersenne_twister_n integers that were produced with an unknown seed and
// reverse engineer the state of the mersenne twister into cloned_state. After this function exits,
// cloned_state will produce values identical to the original mersenne twister starting after the
// first mersenne_twister_n produced values.
void mersenne_twister_clone(const uint32_t* const mt_output, mersenne_twister* const cloned_state);

#pragma once

#include <stdint.h>

#include "utility/mersenne_twister.h"

// Take the given input of mersenne_twister_n integers that were produced with an unknown seed and
// reverse engineer the state of the mersenne twister into cloned_state. After this function exits,
// cloned_state will produce values identical to the original mersenne twister starting after the
// first mersenne_twister_n produced values.
void mersenne_twister_clone(const uint32_t* const mt_output, mersenne_twister* const cloned_state);

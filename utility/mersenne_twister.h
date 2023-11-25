#pragma once

#include <stdint.h>

#define mersenne_twister_w 32u
#define mersenne_twister_n 624u
#define mersenne_twister_u 11u
#define mersenne_twister_d 0xffffffffu
#define mersenne_twister_s 7u
#define mersenne_twister_b 0x9d2c5680u
#define mersenne_twister_t 15u
#define mersenne_twister_c 0xefc60000u
#define mersenne_twister_l 18u

// Holds the state of a MT19937 Mersenne Twister PRNG. Instances of this struct must be initialized
// via mersenne_twister_seed before successful calls to mersenne_twister_next can be made.
typedef struct mersenne_twister {
    // Holds the state array.
    uint32_t mt[mersenne_twister_n];

    // Holds the current index into the state array.
    int index;
} mersenne_twister;

// Get the next value of the MT19937 Mersenne Twister PRNG. The given state must first be
// initialized via mersenne_twister_seed.
uint32_t mersenne_twister_next(mersenne_twister* const mt_state);

// Seed the MT19937 Mersenne Twister PRNG. Calling this function after one or more calls to
// mersenne_twister_next will reset the given state object.
void mersenne_twister_seed(mersenne_twister* const mt_state, uint32_t seed);

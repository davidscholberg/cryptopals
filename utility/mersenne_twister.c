#include <stdint.h>

#include "mersenne_twister.h"

// This implementation of the MT19937 Mersenne Twister PRNG is based off of example code from
// https://en.wikipedia.org/wiki/Mersenne_Twister.

// Generate the next n values for the given mt state.
static void twist(mersenne_twister* const mt_state);

// Constants required for the MT19937 implementation of the Mersenne Twister PRNG:

#define w mersenne_twister_w
#define n mersenne_twister_n
#define m 397u
#define r 31u
#define a 0x9908b0dfu
#define f 1812433253u
#define u mersenne_twister_u
#define d mersenne_twister_d
#define s mersenne_twister_s
#define b mersenne_twister_b
#define t mersenne_twister_t
#define c mersenne_twister_c
#define l mersenne_twister_l

static const uint32_t lower_mask = ((1u << r) - 1);
static const uint32_t upper_mask = (~lower_mask) & 0xffffffff;

uint32_t mersenne_twister_next(mersenne_twister* const mt_state) {
    if (mt_state->index == n) {
        twist(mt_state);
    }

    uint64_t y = mt_state->mt[mt_state->index];
    y = y ^ ((y >> u) & d);
    y = y ^ ((y << s) & b);
    y = y ^ ((y << t) & c);
    y = y ^ (y >> l);

    mt_state->index++;

    return y & 0xffffffff;
}

void mersenne_twister_seed(mersenne_twister* const mt_state, uint32_t seed) {
    mt_state->index = n;
    mt_state->mt[0] = seed;
    for (int i = 1; i < (int)n; i++) {
        uint64_t temp_mt_i = (f * (mt_state->mt[i - 1] ^ (mt_state->mt[i - 1] >> (w - 2)))) + i;
        mt_state->mt[i] = temp_mt_i & 0xffffffff;
    }
}

static void twist(mersenne_twister* const mt_state) {
    for (int i = 0; i < (int)n; i++) {
        uint32_t x = (mt_state->mt[i] & upper_mask) | (mt_state->mt[(i + 1) % n] & lower_mask);
        uint32_t xA = x >> 1;
        if (x % 2 != 0) {
            xA = xA ^ a;
        }
        mt_state->mt[i] = mt_state->mt[(i + m) % n] ^ xA;
    }

    mt_state->index = 0;
}

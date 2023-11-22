#include <stdint.h>

#include "mersenne_twister.h"

// This implementation of the MT19937 Mersenne Twister PRNG is based off of example code from
// https://en.wikipedia.org/wiki/Mersenne_Twister.

// Generate the next n values for mt.
static void twist(void);

// Constants required for the MT19937 implementation of the Mersenne Twister PRNG:

#define w 32u
#define n 624u
#define m 397u
#define r 31u
#define a 0x9908b0dfu
#define f 1812433253u
#define u 11u
#define d 0xffffffffu
#define s 7u
#define b 0x9d2c5680u
#define t 15u
#define c 0xefc60000u
#define l 18u

static const uint32_t lower_mask = ((1u << r) - 1);
static const uint32_t upper_mask = (~lower_mask) & 0xffffffff;

// Holds the current state of the PRNG.
static uint32_t mt[n];

// Current index of the state.
static int index = n + 1;

uint32_t mersenne_twister_next(void) {
    if (index > (int)n) {
        mersenne_twister_seed(0);
    }

    if (index == n) {
        twist();
    }

    uint64_t y = mt[index];
    y = y ^ ((y >> u) & d);
    y = y ^ ((y << s) & b);
    y = y ^ ((y << t) & c);
    y = y ^ (y >> l);

    index++;

    return y & 0xffffffff;
}

void mersenne_twister_seed(uint32_t seed) {
    index = n;
    mt[0] = seed;
    for (int i = 1; i < (int)n; i++) {
        uint64_t temp_mt_i = (f * (mt[i - 1] ^ (mt[i - 1] >> (w - 2)))) + i;
        mt[i] = temp_mt_i & 0xffffffff;
    }
}

static void twist(void) {
    for (int i = 0; i < (int)n; i++) {
        uint32_t x = (mt[i] & upper_mask) | (mt[(i + 1) % n] & lower_mask);
        uint32_t xA = x >> 1;
        if (x % 2 != 0) {
            xA = xA ^ a;
        }
        mt[i] = mt[(i + m) % n] ^ xA;
    }

    index = 0;
}

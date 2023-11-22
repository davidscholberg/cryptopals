#include <stdint.h>

// Get the next value of the MT19937 Mersenne Twister PRNG. If the PRNG was not previously seeded, a
// seed value of 0 is used to initialize the PRNG.
uint32_t mersenne_twister_next(void);

// Seed the MT19937 Mersenne Twister PRNG. Calling this function after one or more calls to
// mersenne_twister_next will reset the state of the PRNG.
void mersenne_twister_seed(uint32_t seed);

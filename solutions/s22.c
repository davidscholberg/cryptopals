#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "oracles/mersenne_twister_oracles.h"
#include "utility/mersenne_twister.h"

// Challenge 22: Given the oracle that seeds the mersenne prng with an unknown time delay value,
// determine what the seed value was. Note that we're simulating the passage of time rather than
// actually passing the time (ain't nobody got time for that, etc.), but the method of determining
// what the seed value was is still the same.
bool s22(char* const out_buffer, const int out_buffer_size) {
    int elapsed_time = 0;
    const unsigned int first_prng_value = mersenne_twister_time_delay_oracle(&elapsed_time);

    int cracked_seed_value = 0;
    for (int i = 0; i < elapsed_time; i++) {
        mersenne_twister_seed(i);
        if (mersenne_twister_next() == first_prng_value) {
            cracked_seed_value = i;
        }
    }

    int bytes_written =
        snprintf(out_buffer, out_buffer_size, "cracked seed value: %d", cracked_seed_value);
    if (bytes_written <= 0 || bytes_written >= out_buffer_size) {
        return false;
    }

    return true;
}

#include "utility/mersenne_twister.h"

unsigned int mersenne_twister_time_delay_oracle(int* const elapsed_time) {
    mersenne_twister_seed(212);
    *elapsed_time = 935;
    return mersenne_twister_next();
}

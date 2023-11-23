#pragma once

// Oracle that simulates passing an unknown amount of time, during which the mersenne twister prng
// is seeded with the current elapsed time, and then returns the first value from the seeded prng.
// Rather than actually passing the time, this function performs the operations immediately and
// tells the caller the simulated amount of time that elapsed.
unsigned int mersenne_twister_time_delay_oracle(int* const elapsed_time);

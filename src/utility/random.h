#pragma once

// Centralized function for initializing the C standard PRNG. This function can be called
// repeatedly, but will only initialize the PRNG on the first call.
void initialize_rand();

// Writes random data to the given buffer. Calls initialize_rand() internally.
void random_buffer(unsigned char* const buffer, const int buffer_size);

#pragma once

// From the given list of buffers containing fixed-nonce CTR encrypted ciphertexts, determine the
// keystream up to the buffer length given, which should ideally be the maximum common buffer size
// if the buffers are of varying lengths. The keystream buffer must have the needed space already
// allocated.
void break_fixed_nonce_ctr(
    const unsigned char** const buffers,
    const int buffer_count,
    const int common_buffer_size,
    unsigned char* const keystream
);

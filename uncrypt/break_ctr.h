#pragma once

// From the given list of buffers containing fixed-nonce CTR encrypted ciphertexts, determine the
// keystream up to the maximum buffer length. The keystream buffer must have the needed space
// already allocated. Note that if the input buffers are of varying lengths, the guessed keystream
// may have inaccuracies towards the end due to an insufficient data size for proper english
// scoring.
void break_fixed_nonce_ctr(
    const unsigned char** const buffers,
    const int* const buffer_sizes,
    const int buffer_count,
    unsigned char* const keystream
);

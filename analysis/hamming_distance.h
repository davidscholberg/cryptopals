#pragma once

// Get the normalized hamming distance of all adjacent block_size pairs in the given buffer. The
// number returned is the average of all adjacent block sized hamming distances divided by the block
// size. If the buffer size does not allow for at least two blocks to be compared, -1 will be
// returned.
float adjacent_blocks_hamming_distance(
    const unsigned char* const buffer,
    const int buffer_size,
    const int block_size
);

// Return the number of bits that differ between the two buffers.
int hamming_distance(
    const unsigned char* const buffer1,
    const unsigned char* const buffer2,
    const int buffer_size
);

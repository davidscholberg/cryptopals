#include "hamming_distance.h"

// Table containing the number of bits set for each possible byte value.
// These numbers were generated with the following python snippet:
//
// for n in range(0, 256):
//     bits_set = 0
//     while n != 0:
//         bits_set += 1
//         n &= n - 1
//     print(f"{bits_set}, ", end="")
//
// This snippet uses Brian Kernighan's algorithm to count bits set.
static const unsigned char bits_set[256] = {
    0, 1, 1, 2, 1, 2, 2, 3, 1, 2, 2, 3, 2, 3, 3, 4, 1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5,
    1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5, 2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
    1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5, 2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
    2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7,
    1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5, 2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
    2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7,
    2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7,
    3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7, 4, 5, 5, 6, 5, 6, 6, 7, 5, 6, 6, 7, 6, 7, 7, 8,
};

float adjacent_blocks_hamming_distance(
    const unsigned char* const buffer,
    const int buffer_size,
    const int block_size
) {
    int block_count = buffer_size / block_size;
    if (block_count == 0) {
        return -1;
    }

    float aggregate_hamming_distance = 0;
    for (int block_index = 0; block_index < block_count - 1; block_index++) {
        int block1_start = block_index * block_size;
        int block2_start = block1_start + block_size;
        aggregate_hamming_distance +=
            hamming_distance(buffer + block1_start, buffer + block2_start, block_size);
    }

    return (aggregate_hamming_distance / (block_count - 1)) / block_size;
}

int hamming_distance(
    const unsigned char* const buffer1,
    const unsigned char* const buffer2,
    const int buffer_size
) {
    int distance = 0;
    for (int i = 0; i < buffer_size; i++) {
        distance += bits_set[buffer1[i] ^ buffer2[i]];
    }
    return distance;
}

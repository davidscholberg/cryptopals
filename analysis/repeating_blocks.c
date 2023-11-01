#include <stdbool.h>
#include <string.h>

int repeating_blocks(const unsigned char* const buffer, int buffer_size, int block_size) {
    int block_count = buffer_size / block_size;
    if (block_count == 0) {
        return 0;
    }

    int repeating_block_count = 0;
    bool seen_repeats[block_count];
    for (int i = 0; i < block_count; i++) seen_repeats[i] = false;

    for (int i = 0; i < block_count - 1; i++) {
        if (seen_repeats[i]) {
            continue;
        }

        bool at_least_one_repeat = false;
        int i_block_start = i * block_size;
        for (int j = i + 1; j < block_count; j++) {
            if (seen_repeats[j]) {
                continue;
            }

            int j_block_start = j * block_size;
            if (!memcmp(buffer + i_block_start, buffer + j_block_start, block_size)) {
                repeating_block_count++;
                seen_repeats[j] = true;
                at_least_one_repeat = true;
            }
        }

        if (at_least_one_repeat) {
            repeating_block_count++;
        }
    }

    return repeating_block_count;
}

#include <limits.h>
#include <stdint.h>

#include "utility/mersenne_twister.h"

// For the given mersenne twister prng output, return the original value from the state array that
// produced it. This essentially reverse engineers a piece of the original state array.
static uint32_t untemper(uint32_t y);

uint16_t crack_mt_stream_seed(
    const unsigned char* const ciphertext,
    const int ciphertext_size,
    const unsigned char target_plaintext_byte,
    const int target_size
) {
    // Determine the keystream values needed to produce the ciphertext assuming that the whole
    // plaintext consisted of target_plaintext_bytes. Note that this assumption only holds for a
    // target_size portion of the plaintext, but that's all we need.
    unsigned char presumed_keystream[ciphertext_size];
    for (int i = 0; i < ciphertext_size; i++) {
        for (int keystream_byte = 0; keystream_byte <= UCHAR_MAX; keystream_byte++) {
            if ((ciphertext[i] ^ keystream_byte) == target_plaintext_byte) {
                presumed_keystream[i] = keystream_byte;
                break;
            }
        }
    }

    // Find a seed value which produces a target_size consecutive run of matches with the presumed
    // keystream. That should be the seed that produced the original keystream that encrypted the
    // ciphertext.
    mersenne_twister mt_state;
    for (int seed = 0; seed <= UINT16_MAX; seed++) {
        mersenne_twister_seed(&mt_state, seed);
        int consecutive_matches = 0;
        for (int i = 0; i < ciphertext_size; i++) {
            const unsigned char keystream_byte = mersenne_twister_next(&mt_state) % (UCHAR_MAX + 1);
            if (keystream_byte == presumed_keystream[i]) {
                consecutive_matches++;
                if (consecutive_matches == target_size) {
                    return seed;
                }
            } else {
                consecutive_matches = 0;
            }
        }
    }

    // We should never reach this point (fingies crossed).
    return 0;
}

void mersenne_twister_clone(const uint32_t* const mt_output, mersenne_twister* const cloned_state) {
    for (int i = 0; i < (int)mersenne_twister_n; i++) {
        cloned_state->mt[i] = untemper(mt_output[i]);
    }

    cloned_state->index = mersenne_twister_n;
}

static uint32_t untemper(uint32_t y) {
    // 4th step reversed
    y = y ^ (y >> mersenne_twister_l);

    // 3rd step reversed
    y = y ^ ((y << mersenne_twister_t) & mersenne_twister_c);

    // 2nd step reversed
    // These masks are meant to capture the lower 7x bits of y.
    uint32_t y_masks_2[] = {0x7fu, 0x3fffu, 0x1fffffu, 0xfffffffu};
    const int y_masks_2_count = sizeof(y_masks_2) / sizeof(y_masks_2[0]);
    // This mask is meant to capture the current 7-bit chunk we're trying to determine.
    const uint32_t bits_to_determine_2 = 0x7fu << mersenne_twister_s;
    for (int i = 0; i < y_masks_2_count; i++) {
        uint32_t y_anded = ((y & y_masks_2[i]) << mersenne_twister_s) & mersenne_twister_b;
        y ^= (bits_to_determine_2 << (i * mersenne_twister_s)) & y_anded;
    }

    // 1st step reversed
    // These masks are meant to capture the upper 11x bits of y.
    uint32_t y_masks_1[] = {0xffe00000u, 0xfffffc00u};
    const int y_masks_1_count = sizeof(y_masks_1) / sizeof(y_masks_1[0]);
    // This mask is meant to capture the current 11-bit chunk we're trying to determine.
    const uint32_t bits_to_determine_1 = 0xffe00000u >> mersenne_twister_u;
    for (int i = 0; i < y_masks_1_count; i++) {
        uint32_t y_shifted = (y & y_masks_1[i]) >> mersenne_twister_u;
        y ^= (bits_to_determine_1 >> (i * mersenne_twister_u)) & y_shifted;
    }

    return y;
}

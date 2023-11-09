#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "utility/pkcs7_pad.h"

#define block_size 16

// Challenge 15: Write a function to validate pkcs7 padding on a buffer.
bool s15(char* const out_buffer, const int out_buffer_size) {
    bool passed = true;

    const char* const valid_padding = "ICE ICE BABY\x04\x04\x04\x04";
    const char* const invalid_padding_1 = "ICE ICE BABY\x05\x05\x05\x05";
    const char* const invalid_padding_2 = "ICE ICE BABY\x01\x02\x03\x04";

    const char* paddings[] = {valid_padding, invalid_padding_1, invalid_padding_2};
    const bool expected_results[] = {true, false, false};
    const int padding_count = sizeof(paddings) / sizeof(paddings[0]);

    for (int i = 0; i < padding_count; i++) {
        const char* const padding = paddings[i];
        const bool expected_result = expected_results[i];
        if (pkcs7_validate((const unsigned char* const)padding, strlen(padding), block_size) !=
            expected_result) {
            passed = false;
            break;
        }
    }

    if (passed) {
        strncpy(out_buffer, "verified all paddings correctly", out_buffer_size);
    } else {
        strncpy(out_buffer, "error verifying one or more paddings", out_buffer_size);
    }

    return true;
}

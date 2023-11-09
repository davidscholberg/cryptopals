#include <stdbool.h>
#include <string.h>

#include "pkcs7_pad.h"

void pkcs7_pad(
    unsigned char* const input_buffer,
    unsigned char* output_buffer,
    int data_size,
    int block_size
) {
    if (output_buffer) {
        memcpy(output_buffer, input_buffer, data_size);
    } else {
        output_buffer = input_buffer;
    }

    int padding_size = pkcs7_padding_needed(data_size, block_size);
    for (int i = data_size; i < data_size + padding_size; i++) {
        output_buffer[i] = padding_size;
    }
}

bool pkcs7_validate(
    const unsigned char* const buffer,
    const int buffer_size,
    const int block_size
) {
    if (buffer_size < block_size || buffer_size % block_size != 0) {
        return false;
    }

    const int padding_size = buffer[buffer_size - 1];
    if (padding_size > block_size) {
        return false;
    }

    for (int i = 1; i < padding_size; i++) {
        if (buffer[buffer_size - 1 - i] != padding_size) {
            return false;
        }
    }

    return true;
}

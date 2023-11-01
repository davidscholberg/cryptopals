#include <string.h>

#include "pkcs7_pad.h"

void pkcs7_pad(
    const unsigned char* const input_buffer,
    unsigned char* const output_buffer,
    int data_size,
    int block_size
) {
    memcpy(output_buffer, input_buffer, data_size);
    int padding_size = pkcs7_padding_needed(data_size, block_size);
    for (int i = data_size; i < data_size + padding_size; i++) {
        output_buffer[i] = padding_size;
    }
}

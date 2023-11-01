#pragma once

// Gives the amount of padding needed for the given amount of data and block size.
#define pkcs7_padding_needed(data_size, block_size) (block_size - (data_size % block_size))

// Gives the amount that the given pkcs7-padded buffer has been padded.
#define pkcs7_padding_size(buffer, buffer_size) (buffer[buffer_size - 1])

// Copy the input buffer into the output buffer and pad it according to the pkcs7 method. Note that
// the output buffer must have the required padding amount allocated (use pkcs7_padding_needed) to
// hold the data and padding, and the given data size must exclude the padding size.
void pkcs7_pad(
    const unsigned char* const input_buffer,
    unsigned char* const output_buffer,
    int data_size,
    int block_size
);

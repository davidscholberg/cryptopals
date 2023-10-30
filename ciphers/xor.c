#include <stdbool.h>

bool xor_byte(
    const unsigned char* const input_buffer,
    const int input_buffer_size,
    const unsigned char input_char,
    unsigned char* const result_buffer,
    const int result_buffer_size,
    const int start,
    const int step
) {
    if (result_buffer_size < input_buffer_size) {
        return false;
    }

    for (int i = start; i < input_buffer_size; i += step) {
        result_buffer[i] = input_buffer[i] ^ input_char;
    }

    return true;
}

bool xor_bytes(
    const unsigned char* const operand1,
    const unsigned char* const operand2,
    const int operand_size,
    unsigned char* const result_buffer,
    const int result_buffer_size
) {
    if (result_buffer_size < operand_size) {
        return false;
    }

    for (int i = 0; i < operand_size; i++) {
        result_buffer[i] = operand1[i] ^ operand2[i];
    }

    return true;
}

bool xor_repeating_key(
    const unsigned char* const input_buffer,
    const int input_buffer_size,
    const unsigned char* const key_buffer,
    const int key_buffer_size,
    unsigned char* const result_buffer,
    const int result_buffer_size
) {
    if (result_buffer_size < input_buffer_size) {
        return false;
    }

    for (int i = 0; i < key_buffer_size; i++) {
        if (!xor_byte(
                input_buffer,
                input_buffer_size,
                key_buffer[i],
                result_buffer,
                result_buffer_size,
                i,
                key_buffer_size
            )) {
            return false;
        }
    }

    return true;
}

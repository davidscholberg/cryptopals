#include <stdbool.h>

bool xor_bytes(
    const unsigned char* const operand1,
    const unsigned char* const operand2,
    const int operand_size,
    unsigned char* const result_buffer,
    const int result_buffer_size
) {
    if (result_buffer_size > operand_size) {
        return false;
    }

    for (int i = 0; i < operand_size; i++) {
        result_buffer[i] = operand1[i] ^ operand2[i];
    }

    return true;
}

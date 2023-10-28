#pragma once

// Take the xor of the two operand byte arrays and store result in result buffer. Returns true on
// success, false if result buffer is smaller than the operands.
bool xor_bytes(
    const unsigned char* const operand1,
    const unsigned char* const operand2,
    const int operand_size,
    unsigned char* const result_buffer,
    const int result_buffer_size
);

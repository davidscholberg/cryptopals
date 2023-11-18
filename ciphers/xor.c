void xor_byte(
    const unsigned char* const input_buffer,
    const int input_buffer_size,
    const unsigned char input_char,
    unsigned char* const result_buffer,
    const int start,
    const int step
) {
    for (int i = start; i < input_buffer_size; i += step) {
        result_buffer[i] = input_buffer[i] ^ input_char;
    }
}

void xor_bytes(
    const unsigned char* const operand1,
    const unsigned char* const operand2,
    unsigned char* const result_buffer,
    const int buffer_size
) {
    for (int i = 0; i < buffer_size; i++) {
        result_buffer[i] = operand1[i] ^ operand2[i];
    }
}

void xor_repeating_key(
    const unsigned char* const input_buffer,
    const int input_buffer_size,
    const unsigned char* const key_buffer,
    const int key_buffer_size,
    unsigned char* const result_buffer
) {
    for (int i = 0; i < key_buffer_size; i++) {
        xor_byte(input_buffer, input_buffer_size, key_buffer[i], result_buffer, i, key_buffer_size);
    }
}

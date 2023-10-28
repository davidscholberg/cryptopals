void repeat_buffer(
    const unsigned char* const input_buffer,
    const int input_buffer_size,
    unsigned char* const output_buffer,
    const int output_buffer_size
) {
    for (int i = 0; i < output_buffer_size; i++) {
        output_buffer[i] = input_buffer[i % input_buffer_size];
    }
}

#include <stdbool.h>

bool hex_to_bytes(
    const char *const hex,
    unsigned char *const byte_buffer,
    const int byte_buffer_size
) {
    for (int i = 0; hex[i] != 0; i++) {
        int byte_index = i / 2;
        if (byte_index >= byte_buffer_size) {
            return false;
        }

        char hex_char = hex[i];
        int ascii_offset = 0;
        if (hex_char >= '0' && hex_char <= '9') {
            ascii_offset = 48;
        } else if (hex_char >= 'A' && hex_char <= 'F') {
            ascii_offset = 55;
        } else if (hex_char >= 'a' && hex_char <= 'f') {
            ascii_offset = 87;
        } else {
            return false;
        }

        int hex_value = hex_char - ascii_offset;
        if (i % 2 == 0) {
            byte_buffer[byte_index] = hex_value << 4;
        } else {
            byte_buffer[byte_index] += hex_value;
        }
    }

    return true;
}

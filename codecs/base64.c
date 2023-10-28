#include <stdbool.h>

#include "base64.h"

#define base64_padding_character '='

static const char *const base64_digits =
    "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

bool bytes_to_base64(
    const unsigned char *const byte_buffer,
    const int byte_buffer_size,
    char *const base64_buffer,
    const int base64_buffer_size
) {
    if (bytes_to_base64_size(byte_buffer_size) > base64_buffer_size) {
        return false;
    }

    int base64_index = 0;
    for (int byte_index = 0; byte_index < byte_buffer_size; byte_index += 3) {
        int sextet_value = byte_buffer[byte_index] >> 2;
        base64_buffer[base64_index] = base64_digits[sextet_value];
        base64_index++;

        sextet_value = (byte_buffer[byte_index] & 0x3) << 4;
        if (byte_index + 1 >= byte_buffer_size) {
            base64_buffer[base64_index] = base64_digits[sextet_value];
            base64_buffer[base64_index + 1] = base64_padding_character;
            base64_buffer[base64_index + 2] = base64_padding_character;
            base64_index += 3;
            break;
        } else {
            sextet_value += byte_buffer[byte_index + 1] >> 4;
            base64_buffer[base64_index] = base64_digits[sextet_value];
            base64_index++;
        }

        sextet_value = (byte_buffer[byte_index + 1] & 0xf) << 2;
        if (byte_index + 2 >= byte_buffer_size) {
            base64_buffer[base64_index] = base64_digits[sextet_value];
            base64_buffer[base64_index + 1] = base64_padding_character;
            base64_index += 2;
            break;
        } else {
            sextet_value += byte_buffer[byte_index + 2] >> 6;
            base64_buffer[base64_index] = base64_digits[sextet_value];
            base64_index++;
        }

        sextet_value = byte_buffer[byte_index + 2] & 0x3f;
        base64_buffer[base64_index] = base64_digits[sextet_value];
        base64_index++;
    }

    base64_buffer[base64_index] = 0;
    return true;
}

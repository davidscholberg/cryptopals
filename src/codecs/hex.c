#include <stdbool.h>
#include <string.h>

#include "hex.h"
#include "log.h"

static const char *const hex_digits = "0123456789abcdef";

bool bytes_to_hex(
    const unsigned char *const byte_buffer,
    const int byte_buffer_size,
    char *const hex_buffer,
    const int hex_buffer_size
) {
    if (hex_buffer_size < bytes_to_hex_size(byte_buffer_size)) {
        log_error("hex buffer too small");
        return false;
    }

    int hex_index = 0;
    for (int i = 0; i < byte_buffer_size; i++) {
        int quartet_value = byte_buffer[i] >> 4;
        hex_buffer[hex_index] = hex_digits[quartet_value];
        hex_index++;

        quartet_value = byte_buffer[i] & 0xf;
        hex_buffer[hex_index] = hex_digits[quartet_value];
        hex_index++;
    }

    hex_buffer[hex_index] = 0;
    return true;
}

bool hex_to_bytes(
    const char *const hex,
    unsigned char *const byte_buffer,
    const int byte_buffer_size
) {
    const int hex_size = strlen(hex);
    if (byte_buffer_size < hex_to_bytes_size(hex_size)) {
        log_error("byte buffer too small");
        return false;
    }

    for (int i = 0; i < hex_size; i++) {
        int byte_index = i / 2;

        char hex_char = hex[i];
        int ascii_offset = 0;
        if (hex_char >= '0' && hex_char <= '9') {
            ascii_offset = 48;
        } else if (hex_char >= 'A' && hex_char <= 'F') {
            ascii_offset = 55;
        } else if (hex_char >= 'a' && hex_char <= 'f') {
            ascii_offset = 87;
        } else {
            log_error("invalid hex character: decimal value: %hhd", hex_char);
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

bool hex_to_bytes_size_wrapper(const char *const hex_string, int *const bytes_size) {
    *bytes_size = hex_to_bytes_size(strlen(hex_string));
    return true;
}

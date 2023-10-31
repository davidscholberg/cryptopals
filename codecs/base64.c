#include <stdbool.h>
#include <string.h>

#include "base64.h"

#define base64_padding_character '='

// Get byte value for the given base64 character. Returns true on success, false on decoding error.
static bool base64_char_to_byte_value(const char base64_char, unsigned char *const byte_value);

static const char *const base64_digits =
    "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

static bool base64_char_to_byte_value(const char base64_char, unsigned char *const byte_value) {
    if (base64_char >= 'A' && base64_char <= 'Z') {
        *byte_value = base64_char - 'A';
        return true;
    }
    if (base64_char >= 'a' && base64_char <= 'z') {
        *byte_value = base64_char - 'a' + 26;
        return true;
    }
    if (base64_char >= '0' && base64_char <= '9') {
        *byte_value = base64_char - '0' + 52;
        return true;
    }
    if (base64_char == '+') {
        *byte_value = 62;
        return true;
    }
    if (base64_char == '/') {
        *byte_value = 63;
        return true;
    }
    return false;
}

bool base64_to_bytes(
    const char *const base64_string,
    unsigned char *const byte_buffer,
    const int byte_buffer_size
) {
    const int base64_string_size = strlen(base64_string);
    int byte_buffer_needed_size = 0;
    if (!base64_to_bytes_size(base64_string, &byte_buffer_needed_size) ||
        byte_buffer_size < byte_buffer_needed_size) {
        return false;
    }

    int byte_buffer_index = 0;
    for (int i = 0; i < base64_string_size; i += 4) {
        unsigned char byte_value = 0;
        if (!base64_char_to_byte_value(base64_string[i], &byte_value)) {
            return false;
        }
        byte_buffer[byte_buffer_index] = byte_value << 2;

        if (!base64_char_to_byte_value(base64_string[i + 1], &byte_value)) {
            return false;
        }
        byte_buffer[byte_buffer_index] += byte_value >> 4;
        if (base64_string[i + 2] == base64_padding_character) {
            return true;
        }
        byte_buffer[byte_buffer_index + 1] = byte_value << 4;

        if (!base64_char_to_byte_value(base64_string[i + 2], &byte_value)) {
            return false;
        }
        byte_buffer[byte_buffer_index + 1] += byte_value >> 2;
        if (base64_string[i + 3] == base64_padding_character) {
            return true;
        }
        byte_buffer[byte_buffer_index + 2] = byte_value << 6;

        if (!base64_char_to_byte_value(base64_string[i + 3], &byte_value)) {
            return false;
        }
        byte_buffer[byte_buffer_index + 2] += byte_value;

        byte_buffer_index += 3;
    }

    return true;
}

bool base64_to_bytes_size(const char *const base64_string, int *const bytes_size) {
    const int base64_string_size = strlen(base64_string);
    if (!is_valid_base64_size(base64_string_size)) {
        return false;
    }

    *bytes_size = (3 * base64_string_size) / 4;
    if (base64_string[base64_string_size - 1] == base64_padding_character) {
        (*bytes_size)--;
    }
    if (base64_string[base64_string_size - 2] == base64_padding_character) {
        (*bytes_size)--;
    }

    return true;
}

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

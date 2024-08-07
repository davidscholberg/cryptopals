#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "codecs/base64.h"
#include "codecs/hex.h"
#include "log.h"

// Challenge 1: Convert the given hex string into a base64 string.
bool s01(char* const out_buffer, const int out_buffer_size) {
    bool status = false;

    static const char* const hex_str =
        "49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e6f7573206d75736872"
        "6f6f6d";
    const int hex_str_size = strlen(hex_str);
    const int byte_buffer_size = hex_to_bytes_size(hex_str_size);
    unsigned char* byte_buffer = malloc(sizeof(unsigned char) * byte_buffer_size);
    if (!byte_buffer) {
        log_error("malloc failed");
        goto s01_clean_exit;
    }

    if (!hex_to_bytes(hex_str, byte_buffer, byte_buffer_size)) {
        log_error("failed to convert hex to bytes");
        goto s01_cleanup_byte_buffer;
    }

    status = bytes_to_base64(byte_buffer, byte_buffer_size, out_buffer, out_buffer_size);

s01_cleanup_byte_buffer:
    free(byte_buffer);

s01_clean_exit:
    return status;
}

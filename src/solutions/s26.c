#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "oracles/user_data_oracle.h"

// This is the size of the data that the oracle prepends to the user data.
#define prefix_size 32
#define known_plaintext_byte 0

// Challenge 26: Do a bit flipping attack to generate an admin string from the CTR ciphertext.
bool s26(char* const out_buffer, const int out_buffer_size) {
    user_data_oracle_set_ctr_mode();

    const char* const user_data_string = "ice_ice_baby";
    const int user_data_string_size = strlen(user_data_string);
    const char* const admin_string = ";admin=true";
    const int admin_string_size = strlen(admin_string);
    const int admin_string_offset = prefix_size + user_data_string_size;
    const int total_user_data_size = user_data_string_size + admin_string_size;
    const int ciphertext_size = user_data_oracle_size(total_user_data_size);
    if (ciphertext_size + 1 > out_buffer_size) {
        return false;
    }

    // Create user data payload with a string of known plaintext bytes where the admin string will
    // go.
    unsigned char total_user_data[total_user_data_size];
    for (int i = 0; i < total_user_data_size; i++) {
        if (i < user_data_string_size) {
            total_user_data[i] = user_data_string[i];
        } else {
            total_user_data[i] = known_plaintext_byte;
        }
    }
    unsigned char hax0red_ciphertext[ciphertext_size];
    user_data_oracle(total_user_data, total_user_data_size, hax0red_ciphertext);

    // Determine keystream at admin string location and flip bits in the admin string offset in
    // order to get the admin string on decryption.
    for (int i = 0; i < admin_string_size; i++) {
        const int admin_string_i = admin_string_offset + i;
        for (int keystream_byte = 0; keystream_byte <= UCHAR_MAX; keystream_byte++) {
            if ((keystream_byte ^ known_plaintext_byte) == hax0red_ciphertext[admin_string_i]) {
                hax0red_ciphertext[admin_string_i] = keystream_byte ^ admin_string[i];
                break;
            }
        }
    }

    // Recover plaintext with admin string in it.
    user_data_oracle_decrypt(hax0red_ciphertext, ciphertext_size, (unsigned char* const)out_buffer);
    out_buffer[ciphertext_size] = 0;

    return true;
}

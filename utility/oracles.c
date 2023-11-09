#include <stdlib.h>
#include <string.h>

#include "ciphers/aes.h"
#include "oracles.h"
#include "pkcs7_pad.h"

static const char* const aes_ecb_or_cbc_oracle_prefix =
    "Rollin' in my 5.0 With my rag-top down so my hair can blow";
static const char* const aes_ecb_or_cbc_oracle_suffix = "Cooking MC's like a pound of bacon";

bool aes_ecb_or_cbc_oracle(
    const unsigned char* const plaintext,
    const int plaintext_size,
    unsigned char* const ciphertext
) {
    static const char* const key = "RobertMatthewVW.";
    static const char* const iv = "Iceman Robbie...";

    const int prefix_size = strlen(aes_ecb_or_cbc_oracle_prefix);
    const int suffix_size = strlen(aes_ecb_or_cbc_oracle_suffix);
    memcpy(ciphertext, aes_ecb_or_cbc_oracle_prefix, prefix_size);
    memcpy(ciphertext + prefix_size, plaintext, plaintext_size);
    memcpy(ciphertext + prefix_size + plaintext_size, aes_ecb_or_cbc_oracle_suffix, suffix_size);

    const int total_data_size = prefix_size + plaintext_size + suffix_size;
    pkcs7_pad(ciphertext, NULL, total_data_size, aes_block_size);
    const int total_buffer_size =
        total_data_size + pkcs7_padding_needed(total_data_size, aes_block_size);

    static int call_count = 0;

    if (call_count % 2) {
        // we're doing cbc
        if (!aes_cbc_encrypt(
                ciphertext,
                total_buffer_size,
                NULL,
                (const unsigned char* const)iv,
                (const unsigned char* const)key
            )) {
            return false;
        }
    } else {
        // we're doing ecb
        if (!aes_ecb_encrypt(
                ciphertext,
                total_buffer_size,
                NULL,
                (const unsigned char* const)key
            )) {
            return false;
        }
    }

    call_count++;

    return true;
}

int aes_ecb_or_cbc_oracle_size(const int plaintext_size) {
    const int total_data_size = plaintext_size + strlen(aes_ecb_or_cbc_oracle_prefix) +
        strlen(aes_ecb_or_cbc_oracle_suffix);
    return total_data_size + pkcs7_padding_needed(total_data_size, aes_block_size);
}

// Secret text that gets appended to the plaintext input of aes_ecb_oracle. Challenge 12 calls for
// this string to be initially base64 encoded, but I don't think that pre-decoding it has any
// bearing on successfully completing the challenge.
static const char* const aes_ecb_oracle_suffix =
    "Rollin' in my 5.0\nWith my rag-top down so my hair can blow\nThe girlies on standby waving "
    "just to say hi\nDid you stop? No, I just drove by\n";

bool aes_ecb_oracle(
    const unsigned char* const plaintext,
    const int plaintext_size,
    unsigned char* const ciphertext
) {
    static const char* const key = "iceicebabyiceice";

    memcpy(ciphertext, plaintext, plaintext_size);

    const int sectret_text_size = strlen(aes_ecb_oracle_suffix);
    memcpy(ciphertext + plaintext_size, aes_ecb_oracle_suffix, sectret_text_size);

    const int total_data_size = plaintext_size + sectret_text_size;
    pkcs7_pad(ciphertext, NULL, total_data_size, aes_block_size);

    const int padded_plaintext_size = aes_ecb_oracle_size(plaintext_size);
    return aes_ecb_encrypt(
        ciphertext,
        padded_plaintext_size,
        NULL,
        (const unsigned char* const)key
    );
}

int aes_ecb_oracle_size(const int plaintext_size) {
    const int total_data_size = plaintext_size + strlen(aes_ecb_oracle_suffix);
    return total_data_size + pkcs7_padding_needed(total_data_size, aes_block_size);
}

static const char* const aes_ecb_with_prefix_oracle_prefix = "Cooking MC's like a pound of bacon";
static const char* const aes_ecb_with_prefix_oracle_suffix =
    "Burning them, if you ain't quick and nimble\nI go crazy when I hear a cymbal\nAnd a hi-hat "
    "with a souped up tempo\nI'm on a roll, it's time to go solo\n";

bool aes_ecb_with_prefix_oracle(
    const unsigned char* const plaintext,
    const int plaintext_size,
    unsigned char* const ciphertext
) {
    static const char* const key = "iceicebabybaby!!";

    const int prefix_size = strlen(aes_ecb_with_prefix_oracle_prefix);
    memcpy(ciphertext, aes_ecb_with_prefix_oracle_prefix, prefix_size);
    memcpy(ciphertext + prefix_size, plaintext, plaintext_size);
    const int suffix_size = strlen(aes_ecb_with_prefix_oracle_suffix);
    memcpy(
        ciphertext + prefix_size + plaintext_size,
        aes_ecb_with_prefix_oracle_suffix,
        suffix_size
    );

    const int total_data_size = prefix_size + plaintext_size + suffix_size;
    pkcs7_pad(ciphertext, NULL, total_data_size, aes_block_size);
    const int padded_data_size =
        total_data_size + pkcs7_padding_needed(total_data_size, aes_block_size);

    return aes_ecb_encrypt(ciphertext, padded_data_size, NULL, (const unsigned char* const)key);
}

int aes_ecb_with_prefix_oracle_size(const int plaintext_size) {
    const int total_data_size = strlen(aes_ecb_with_prefix_oracle_prefix) + plaintext_size +
        strlen(aes_ecb_with_prefix_oracle_suffix);
    return total_data_size + pkcs7_padding_needed(total_data_size, aes_block_size);
}

static const char* const profile_prefix = "email=";
static const char* const profile_suffix = "&uid=10&role=user";
static const char* const profile_secret_key = "vanilla||allinav";

bool encrypted_profile_decrypt(
    unsigned char* const ciphertext,
    const int ciphertext_size,
    unsigned char* const plaintext
) {
    return aes_ecb_decrypt(
        ciphertext,
        ciphertext_size,
        plaintext,
        (const unsigned char* const)profile_secret_key
    );
}

bool encrypted_profile_oracle(
    const unsigned char* const email,
    const int email_size,
    unsigned char* const ciphertext
) {
    const int profile_prefix_size = strlen(profile_prefix);
    memcpy(ciphertext, profile_prefix, profile_prefix_size);
    memcpy(ciphertext + profile_prefix_size, email, email_size);
    const int profile_suffix_size = strlen(profile_suffix);
    memcpy(ciphertext + profile_prefix_size + email_size, profile_suffix, profile_suffix_size);

    const int data_size = profile_prefix_size + email_size + profile_suffix_size;
    pkcs7_pad(ciphertext, NULL, data_size, aes_block_size);
    const int padded_data_size = data_size + pkcs7_padding_needed(data_size, aes_block_size);

    return aes_ecb_encrypt(
        ciphertext,
        padded_data_size,
        NULL,
        (const unsigned char* const)profile_secret_key
    );
}

int encrypted_profile_oracle_size(const int email_size) {
    const int data_size = email_size + strlen(profile_prefix) + strlen(profile_suffix);
    return data_size + pkcs7_padding_needed(data_size, aes_block_size);
}

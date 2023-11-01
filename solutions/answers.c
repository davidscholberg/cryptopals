#include <stddef.h>

// Array of all available challenge answers.
static const char* const answers[] = {
    "SSdtIGtpbGxpbmcgeW91ciBicmFpbiBsaWtlIGEgcG9pc29ub3VzIG11c2hyb29t",
    "746865206b696420646f6e277420706c6179",
    "Cooking MC's like a pound of bacon",
    "Now that the party is jumping\n",
    "0b3637272a2b2e63622c2e69692a23693a2a3c6324202d623d63343c2a26226324272765272a282b2f20430a652e2c"
    "652a3124333a653e2b2027630c692b20283165286326302e27282f",
    "Terminator X: Bring the noise",
    "I'm back and I'm ringin' the bell ",
};

// Number of items in the answers array.
static const int answers_size = sizeof(answers) / sizeof(answers[0]);

const char* get_answer(const int n) {
    if (n >= answers_size) {
        return NULL;
    }
    return answers[n];
}

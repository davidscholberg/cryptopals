#include <stddef.h>

// Array of all available challenge answers.
static const char* const answers[] = {
    "SSdtIGtpbGxpbmcgeW91ciBicmFpbiBsaWtlIGEgcG9pc29ub3VzIG11c2hyb29t",
    "746865206b696420646f6e277420706c6179",
    "Cooking MC's like a pound of bacon",
    "Now that the party is jumping\n",
};

// Number of items in the answers array.
static const int answers_size = sizeof(answers) / sizeof(answers[0]);

const char* get_answer(const int n) {
    if (n >= answers_size) {
        return NULL;
    }
    return answers[n];
}

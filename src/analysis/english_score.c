#include <stdbool.h>

#include "english_score.h"

#define is_lowercase_letter(character) (character >= 'a' && character <= 'z')
#define is_uppercase_letter(character) (character >= 'A' && character <= 'Z')

// Array of letter frequencies for English. Letter frequencies are indexed by their letter's ascii
// code minus 65 for uppercase and minus 97 for lowercase.
//
// Source: https://en.wikipedia.org/wiki/Letter_frequency
static const float letter_frequencies[] = {
    8.2, 1.5, 2.8, 4.3,   12.7, 2.2, 2.0, 6.1, 7.0,  0.15, 0.77, 4.0, 2.4,
    6.7, 7.5, 1.9, 0.095, 6.0,  6.3, 9.1, 2.8, 0.98, 2.4,  0.15, 2.0, 0.074,
};

// Array of letter frequencies for the first letter of English words. Letter frequencies are indexed
// by their letter's ascii code minus 65 for uppercase and minus 97 for lowercase.
//
// Source: https://en.wikipedia.org/wiki/Letter_frequency
static const float first_letter_frequencies[] = {
    11.7, 4.4, 5.2, 3.2,  2.8, 4,   1.6, 4.2, 7.3,  0.51, 0.86,  2.4,  3.8,
    2.3,  7.6, 4.3, 0.22, 2.8, 6.7, 16,  1.2, 0.82, 5.5,  0.045, 0.76, 0.045,

};

// Frequency of the space character in English text.
//
// Source:
// https://www.researchgate.net/figure/Probability-of-characters-in-English-The-SPACE-character-represented-by-has-the_fig2_47518347
static const float space_frequency = 20;

float english_score(
    const unsigned char* const buffer,
    const int buffer_size,
    bool first_letters,
    const int start,
    const int step
) {
    float score = 0;
    for (int i = start; i < buffer_size; i += step) {
        if (!first_letters && is_lowercase_letter(buffer[i])) {
            score += letter_frequencies[buffer[i] - 'a'];
        } else if (is_uppercase_letter(buffer[i])) {
            if (first_letters) {
                score += first_letter_frequencies[buffer[i] - 'A'];
            } else {
                score += letter_frequencies[buffer[i] - 'A'];
            }
        } else if (!first_letters && buffer[i] == ' ') {
            score += space_frequency;
        }
    }

    return score;
}

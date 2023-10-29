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

// Frequency of the space character in English text.
//
// Source:
// https://www.researchgate.net/figure/Probability-of-characters-in-English-The-SPACE-character-represented-by-has-the_fig2_47518347
static const float space_frequency = 20;

float english_score(
    const unsigned char* const buffer,
    const int buffer_size,
    const int start,
    const int step
) {
    float score = 0;
    for (int i = start; i < buffer_size; i += step) {
        if (is_lowercase_letter(buffer[i])) {
            score += letter_frequencies[buffer[i] - 'a'];
        } else if (is_uppercase_letter(buffer[i])) {
            score += letter_frequencies[buffer[i] - 'A'];
        } else if (buffer[i] == ' ') {
            score += space_frequency;
        }
    }

    return score;
}

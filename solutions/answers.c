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
    "d880619740a8a19b7840a8a31c810a3d08649af70dc06f4fd5d2d69c744cd283e2dd052f6b641dbf9d11b0348542bb"
    "5708649af70dc06f4fd5d2d69c744cd2839475c9dfdbc1d46597949d9c7e82bf5a08649af70dc06f4fd5d2d69c744c"
    "d28397a93eab8d6aecd566489154789a6b0308649af70dc06f4fd5d2d69c744cd283d403180c98c8f6db1f2a3f9c40"
    "40deb0ab51b29933f2c123c58386b06fba186a",
    "59454c4c4f57205355424d4152494e4504040404",
    "I'm back and I'm ringin' the bell ",
    "guessed all cipher modes correctly",
    "Rollin' in my 5.0\nWith my rag-top down so my hair can blow\nThe girlies on standby waving "
    "just to say hi\nDid you stop? No, I just drove by\n",
    "email=aaaaaaa@a.com&uid=10&role=admin",
    "Burning them, if you ain't quick and nimble\nI go crazy when I hear a cymbal\nAnd a hi-hat "
    "with a souped up tempo\nI'm on a roll, it's time to go solo\n",
    "verified all paddings correctly",
    "successfully flipped bits to get admin string",
    "With the bass kicked in and the Vega's are pumpin'",
    "Yo, VIP Let's kick it Ice, Ice, baby Ice, Ice, baby ",
    "I have met them at c",
    "I'm rated \"R\"...this is a warning, ya better void / P",
    "39, 3, 20, 78, 62, 51, 78, 64, 99, 35, 84, 79, 25, 32, 19, 5, 68, 80, 32, 37",
    "cracked seed value: 212",
    "62, 85, 67, 44, 54, 15, 59, 45, 26, 85, 97, 88, 75, 19, 75, 0, 40, 76, 42, 39",
    "cracked seed value: 5649",
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

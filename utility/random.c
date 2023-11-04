#include <limits.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

void initialize_rand() {
    static bool has_been_initialized = false;
    if (!has_been_initialized) {
        srand(time(NULL));
        has_been_initialized = true;
    }
}

void random_buffer(unsigned char* const buffer, const int buffer_size) {
    initialize_rand();
    for (int i = 0; i < buffer_size; i++) {
        buffer[i] = rand() % UCHAR_MAX;
    }
}

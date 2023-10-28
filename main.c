#include <stdio.h>
#include <stdlib.h>

#include "solutions/run.h"

#define computed_answer_buffer_size 1024

int main(const int argc, const char** const argv) {
    const char* const usage = "usage: %s [challenge number]\n";
    if (argc != 2) {
        printf("error: invalid number of arguments\n");
        printf(usage, argv[0]);
        return EXIT_FAILURE;
    }
    const int n = atoi(argv[1]);
    if (n <= 0) {
        printf("error: invalid challenge number\n");
        printf(usage, argv[0]);
        return EXIT_FAILURE;
    }

    char computed_answer[computed_answer_buffer_size];
    const solution_status status =
        run_solution(n - 1, computed_answer, computed_answer_buffer_size);
    if (status == solution_not_found) {
        printf("error: solution not found for challenge %d\n", n);
        return EXIT_FAILURE;
    }
    if (status == solution_failure) {
        printf("error: solution failed for challenge %d\n", n);
        return EXIT_FAILURE;
    }
    printf("challenge %d\n", n);
    printf("computed answer: %s\n", computed_answer);

    return EXIT_SUCCESS;
}

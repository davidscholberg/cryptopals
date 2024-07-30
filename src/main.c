#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "solutions/answers.h"
#include "solutions/run.h"

#define computed_answer_buffer_size 10240

int main(const int argc, const char** const argv) {
    const char* const usage = "usage: %s challenge_number|all\n";
    if (argc != 2) {
        printf("error: invalid number of arguments\n");
        printf(usage, argv[0]);
        return EXIT_FAILURE;
    }

    int solution_number = 1;
    int solutions_to_run = 1;
    if (!strcmp(argv[1], "all")) {
        solutions_to_run = solutions_size;
    } else {
        solution_number = atoi(argv[1]);
        if (solution_number <= 0) {
            printf("error: invalid challenge number\n");
            printf(usage, argv[0]);
            return EXIT_FAILURE;
        }
    }

    char computed_answer[computed_answer_buffer_size];
    int exit_status = EXIT_SUCCESS;
    for (int i = 0; i < solutions_to_run; i++) {
        const int n = solution_number + i;
        const solution_status status =
            run_solution(n - 1, computed_answer, computed_answer_buffer_size);
        if (status == solution_not_found) {
            printf("❌ solution not found for challenge %d\n", n);
            exit_status = EXIT_FAILURE;
            continue;
        }
        if (status == solution_failure) {
            printf("❌ solution failed for challenge %d\n", n);
            exit_status = EXIT_FAILURE;
            continue;
        }

        if (i > 0) {
            printf("\n");
        }

        printf("challenge %d\n", n);
        printf("computed answer: %s\n", computed_answer);
        const char* const correct_answer = get_answer(n - 1);
        if (correct_answer == NULL) {
            printf("❔ correct answer not found\n");
            continue;
        }
        printf("correct answer:  %s\n", correct_answer);
        if (strcmp(computed_answer, correct_answer)) {
            printf("❌ back to the drawing board\n");
        } else {
            printf("✅ you got it!\n");
        }
    }

    return exit_status;
}

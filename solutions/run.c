#include <stdbool.h>

#include "run.h"
#include "solutions.h"

// Function pointer type for solution functions.
//
// A solution function is a function that solves a specific cryptopals challenge. The inputs are a
// string buffer and size. The function is meant to write the computed answer to the string buffer.
// The return value tells if the function succeeded or not.
typedef bool (*solution)(char* const, const int);

// Array of all implemented solutions.
static const solution solutions[] = {
    s01, s02, s03, s04, s05, s06, s07, s08, s09, s10, s11, s12,
    s13, s14, s15, s16, s17, s18, s19, s20, s21, s22, s23, s24,
};

// Number of items in the solutions array.
const int solutions_size = sizeof(solutions) / sizeof(solution);

solution_status run_solution(const int n, char* const out_buffer, const int out_buffer_size) {
    if (n >= solutions_size) {
        return solution_not_found;
    }
    const bool success = solutions[n](out_buffer, out_buffer_size);
    return success ? solution_success : solution_failure;
}

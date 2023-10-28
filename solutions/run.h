#pragma once

// Enum used to indicate the exit status of the run_solution function.
typedef enum solution_status {
    solution_not_found,
    solution_success,
    solution_failure
} solution_status;

// Run the solution for the given cryptopals challenge.
//
// n will be used as an index of the array of challenge solutions and therefore should be one less
// than the corresponding challenge number. The passed-in string buffer will have the computed
// answer written to it.
solution_status run_solution(const int n, char* const out_buffer, const int out_buffer_size);

#pragma once

// Place the given multiline string into the given one-line string with newlines removed. The space
// for one_line_str must be allocated by the caller, and you can get the exact size needed with the
// concat_lines_size function.
void concat_lines(const char* const multiline_str, char* const one_line_str);

// Returns the size required to hold the given string if all newlines were removed. The returned
// size includes the trailing null byte.
int concat_lines_size(const char* const multiline_str);

// Split the given string into an array of strings on the newline character. The number of splits
// will be placed in split_count, and the return value is a malloced address to an array of string
// pointers or null on error.
char** split_string(const char* const multiline_str, int* const split_count);

#pragma once

// Place the given multiline string into the given one-line string with newlines removed. The space
// for one_line_str must be allocated by the caller, and you can get the exact size needed with the
// concat_lines_size function.
void concat_lines(const char* const multiline_str, char* const one_line_str);

// Returns the size of the given string if all newlines were removed.
int concat_lines_size(const char* const multiline_str);

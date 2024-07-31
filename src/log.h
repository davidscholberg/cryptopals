#pragma once

#include <stdio.h> // IWYU pragma: export

// Convert non-string constant to string.
// NOTE: this does not belong here ideally.
#define stringify_the_second(non_str) #non_str
#define stringify(non_str) stringify_the_second(non_str)

// Strings to be prepended to message types.
#define log_error_tag "error: "

// Logs the given message with file, line number, and function name. Behaves like printf except the
// given format string must be a string literal. A newline is added after the given format string.
// This macro should be called by the log macro, which allows you to optionally pass va_args (I
// would be using va_opt here but clangd still hasn't caught up to c23 yet).
#define log_helper(tag, message, ...) \
    printf( \
        "cryptopals: " tag __FILE__ ":" stringify(__LINE__) ": in function %s: " message "%s", \
        __func__, \
        __VA_ARGS__)

// Helper macro that adds a newline string to va_args so that it is always defined for log_helper
// (substitute for va_opt until clangd catches up).
#define log(...) log_helper(__VA_ARGS__, "\n")

// Convenience macros for logging different message types.
#define log_error(...) log(log_error_tag, __VA_ARGS__)

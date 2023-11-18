#include <linux/limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define default_path_size PATH_MAX

// Returns number of lines in the buffer. The given file buffer must not have any empty lines except
// for the last line, which must be empty.
int buffer_line_count(const unsigned char* const buffer, const int buffer_size);

// Returns the size of the given file or a negative value indicating an error from either fseek or
// ftell. Note that the stream position is reset back to the beginning.
long file_size(FILE* file);

// Reads file contents into the given buffer up to given buffer size. Returns total bytes written on
// success or -1 on error.
int file_to_buffer(FILE* file, unsigned char* const buffer, const int buffer_size);

// Given the filename of a resource file, put the full path to the resource file in full_path. The
// return value is equivalent to the return value of snprintf.
int full_resource_path(char* const full_path, int full_path_size, const char* const filename);

static const char* const resources_relative_fmt = "resources/%s";

int buffer_line_count(const unsigned char* const buffer, const int buffer_size) {
    int count = 0;

    for (int i = 1; i < buffer_size; i++) {
        if (buffer[i] == '\n') {
            count++;
        }
    }

    return count;
}

long file_size(FILE* file) {
    int ret = fseek(file, 0, SEEK_END);
    if (ret) {
        return ret;
    }

    long size = ftell(file);
    if (size == -1) {
        return size;
    }

    ret = fseek(file, 0, SEEK_SET);
    if (ret) {
        return ret;
    }

    return size;
}

int file_to_buffer(FILE* file, unsigned char* const buffer, const int buffer_size) {
    int bytes_read = fread(buffer, 1, buffer_size, file);
    if (ferror(file)) {
        return -1;
    }

    return bytes_read;
}

char** file_to_lines(const char* const filename, int* const line_count_ptr) {
    *line_count_ptr = 0;

    // Get full path to file.
    char full_path[default_path_size];
    int ret = full_resource_path(full_path, default_path_size, filename);
    if (ret <= 0 || ret >= default_path_size) {
        return NULL;
    }

    // Get file size.
    FILE* file = fopen(full_path, "r");
    if (!file) {
        return NULL;
    }
    long file_buffer_size = file_size(file);
    if (file_buffer_size <= 0) {
        fclose(file);
        return NULL;
    }

    // Read file into buffer.
    char file_buffer[file_buffer_size];
    if (file_to_buffer(file, (unsigned char* const)file_buffer, file_buffer_size) !=
        file_buffer_size) {
        fclose(file);
        return NULL;
    }
    fclose(file);

    // Count lines and allocate memory for lines buffer.
    int line_count = buffer_line_count((unsigned char* const)file_buffer, file_buffer_size);
    int line_ptrs_size = line_count * sizeof(char*);
    unsigned char* line_ptrs_and_buffer = malloc(line_ptrs_size + file_buffer_size);
    if (!line_ptrs_and_buffer) {
        return NULL;
    }

    // Write lines to lines buffer
    char** line_ptr = (char**)line_ptrs_and_buffer;
    char* line_buffer = (char*)line_ptrs_and_buffer + line_ptrs_size;
    char* line_start = line_buffer;
    for (int i = 0; i < file_buffer_size; i++) {
        if (file_buffer[i] == '\n') {
            line_buffer[i] = 0;
            *line_ptr = line_start;
            line_ptr++;
            line_start = line_buffer + i + 1;
        } else {
            line_buffer[i] = file_buffer[i];
        }
    }

    *line_count_ptr = line_count;
    return (char**)line_ptrs_and_buffer;
}

int full_resource_path(char* const full_path, int full_path_size, const char* const filename) {
    char resources_full_fmt[default_path_size];
    int ret = readlink("/proc/self/exe", resources_full_fmt, default_path_size);
    if (ret <= 0 || ret >= default_path_size) {
        return ret;
    }

    char* fmt_overwrite = strrchr(resources_full_fmt, '/');
    if (!fmt_overwrite) {
        return 0;
    }
    *(fmt_overwrite + 1) = 0;

    if (strlen(resources_full_fmt) + strlen(resources_relative_fmt) + 1 > default_path_size) {
        return 0;
    }
    strcat(resources_full_fmt, resources_relative_fmt);

    return snprintf(full_path, full_path_size, resources_full_fmt, filename);
}
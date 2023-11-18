#include <stdlib.h>
#include <string.h>

#include "decode_lines.h"

unsigned char **decode_lines(
    char **lines,
    const int line_count,
    decode_fn decode,
    decode_size_fn decode_size,
    int **buffer_sizes_ptr
) {
    // Calculate size of decoded lines memory and allocate it
    const int buffer_ptrs_size = line_count * sizeof(unsigned char *);
    const int buffer_sizes_size = line_count * sizeof(int);
    int buffers_size = 0;
    int buffer_size = 0;
    int temp_buffer_sizes[line_count];
    for (int i = 0; i < line_count; i++) {
        if (!decode_size(lines[i], &buffer_size)) {
            return NULL;
        }
        buffers_size += buffer_size;
        temp_buffer_sizes[i] = buffer_size;
    }
    unsigned char *decoded_buffers_mem =
        malloc(buffer_ptrs_size + buffer_sizes_size + buffers_size);
    if (!decoded_buffers_mem) {
        return NULL;
    }
    unsigned char **buffers = (unsigned char **)decoded_buffers_mem;
    int *buffer_sizes = (int *)(decoded_buffers_mem + buffer_ptrs_size);
    unsigned char *buffers_start = decoded_buffers_mem + buffer_ptrs_size + buffer_sizes_size;

    // Loop through strings and decode
    unsigned char *current_buffer = buffers_start;
    for (int i = 0; i < line_count; i++) {
        buffers[i] = current_buffer;
        const int buffer_size = temp_buffer_sizes[i];
        buffer_sizes[i] = buffer_size;
        if (!decode(lines[i], current_buffer, buffer_size)) {
            free(buffers);
            return NULL;
        }
        current_buffer += buffer_size;
    }

    *buffer_sizes_ptr = buffer_sizes;
    return buffers;
}

#pragma once

// Return the number of repeating blocks in the given buffer. The returned number is a count of
// every single block that has at least one additional copy elsewhere in the buffer.
int repeating_blocks(const unsigned char* const buffer, int buffer_size, int block_size);

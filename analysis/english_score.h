#pragma once

// Generate a score for the input buffer that represents the likelyhood that the buffer is english
// text.
float english_score(const unsigned char* const buffer, const int buffer_size);

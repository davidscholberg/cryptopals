#pragma once

// Generate a score for the input buffer that represents the likelyhood that the buffer is english
// text. The start parameter indicates an offset for where to start scorint. The step parameter
// should be set to 1 if you want to score contiguous values in the input buffer, or greater than
// one if you want to score values that are not contiguous but evenly spaced.
float english_score(
    const unsigned char* const buffer,
    const int buffer_size,
    const int start,
    const int step
);

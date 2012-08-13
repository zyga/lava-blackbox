#ifndef TEXT_UTILS_H
#define TEXT_UTILS_H

#include <stdio.h>

/**
 * Read one line from stream.
 *
 * This function allocates the memory on demand, reusing any previous
 * buffers if possible. The buffer data is kept in two variables that must
 * be provided by the caller.
 *
 * Uses text_grow_buffer() and can fail the same way.
 **/
int
text_readline(
    char **buffer_ptr,
    size_t *capacity_ptr,
    FILE *stream
    );


/**
 * Copy specified text into the specified buffer.
 *
 * Uses text_grow_buffer() and can fail the same way.
 **/
int
text_copy(
    char **buffer_ptr,
    size_t *capacity_ptr,
    const char *text
    );


/**
 * Grow the text buffer so that it can hold at lest the specified required
 * capacity of bytes.
 *
 * Returns 0 on success. On out-of-memory error the old line buffer and
 * capacity are left intact and it is expected that the caller will free
 * that buffer.
 **/
int
text_grow_buffer(
    char **buffer_ptr,
    size_t *capacity_ptr,
    size_t min_capacity
    );

#endif

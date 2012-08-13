#include "text-utils.h"

#include <errno.h>
#include <stdlib.h>
#include <string.h>

#include "debug.h"


int
text_readline(
    char **buffer_ptr,
    size_t *capacity_ptr,
    FILE *stream
    )
{
    int c;
    size_t size = 0;
    char *buffer;
    size_t capacity;
    int error;
    /* Ensure the caller passed line and capacity pointers */
    if (buffer_ptr == NULL || capacity_ptr == NULL)
        return EINVAL;
    buffer = *buffer_ptr;
    capacity = *capacity_ptr;
    do {
        text_grow_buffer(&buffer, &capacity, size + 1);
        /* Do the IO, read one byte at a time */
        c = fgetc(stream);
        if (c != EOF && c != '\n') {
            buffer[size++] = (char)c;
        } else {
            buffer[size++] = 0;
            break;
        }
    } while (1);
    error = 0;
out:
    /* Copy back the line and capacity */
    *buffer_ptr = buffer;
    *capacity_ptr = capacity;
    return error;
}


int
text_copy(
    char **buffer_ptr,
    size_t *capacity_ptr,
    const char *text
    )
{
    size_t text_len;
    int error;
    /* Ensure the caller passed line and capacity pointers */
    if (buffer_ptr == NULL || capacity_ptr == NULL)
        return EINVAL;
    if (text == NULL)
        return EINVAL;
    text_len = strlen(text);
    error = text_grow_buffer(buffer_ptr, capacity_ptr, text_len + 1);
    if (error != 0)
        return error;
    strncpy(*buffer_ptr, text, *capacity_ptr);
    return 0;
}


/**
 * Find a good reallocation size for the current size
 **/
static
size_t
next_best_capacity(size_t size) {
    const size_t good_sizes[] = {128, 512, 4 * 1024, 16 * 1024};
    size_t i;
    /* Try to use one of the good sizes */
    for (i=0; i<sizeof(good_sizes) / sizeof(*good_sizes); ++i)
        if (size < good_sizes[i])
            return good_sizes[i];
    /* Or just double the current size */
    return size * 2;
}


int
text_grow_buffer(
    char **buffer_ptr,
    size_t *capacity_ptr,
    size_t min_capacity
    )
{
    char *buffer, *new_buffer;
    size_t capacity, new_capacity;
    /* Ensure the caller passed line and capacity pointers */
    if (buffer_ptr == NULL || capacity_ptr == NULL)
        return EINVAL;
    /* Load current buffer pointer and size */
    buffer = *buffer_ptr;
    capacity = *capacity_ptr;
    /* Keep growing the buffer as required */
    while (capacity <= min_capacity) {
        new_capacity = next_best_capacity(min_capacity);
        debug_log("Resizing text buffer from %zd to %zd bytes\n",
                  capacity, new_capacity);
        new_buffer = realloc(buffer, new_capacity);
        if (new_buffer != NULL) {
            debug_log("Resize complete, old buffer %p, new buffer %p\n",
                      buffer, new_buffer);
            buffer = new_buffer;
            capacity = new_capacity;
        } else {
            debug_log("Unable to resize line buffer!\n");
            return ENOMEM;
        }
    }
    /* Copy back the new buffer pointer and new capacity */
    *buffer_ptr = buffer;
    *capacity_ptr = capacity;
    return 0;
}

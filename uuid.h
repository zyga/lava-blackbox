#ifndef UUID_H
#define UUID_H

/**
 * Pathname of a special file that generates UUID on read
 **/
#define UUID_PATHNAME "/proc/sys/kernel/random/uuid"

/**
 * Number of bytes, not including the final nul byte, required to store an UUID in text form
 **/
#define UUID_ASCII_LEN 36

/**
 * Generate a random UUID by reading from UUID_PATHNAME
 *
 * The buffer must have at least UUID_ASCII_LEN + 1 bytes.
 * Returns 0 on success.
 **/

int
uuid_gen(char *buf);

#endif

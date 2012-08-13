#ifndef JSON_FORMAT_H
#define JSON_FORMAT_H

#include <stdio.h>

/* Token for JSON pieces.
 *
 * Used as simple command language to write JSON documents */
enum json_token {
    /* End of commands marker */
    JSON_END,
    /* Prints '{' */
    JSON_DICT_START,
    /* Prints '}' */
    JSON_DICT_END,
    /* Prints '[' */
    JSON_ARRAY_START,
    /* Prints ']' */
    JSON_ARRAY_END,
    /* Prints ',' */
    JSON_COMMA,
    /* Prints ':' */
    JSON_COLON,
    /* Prints '\n' but only in human readable mode */
    JSON_NEWLINE,
    /* Prints ' ' but only in human readable mode */
    JSON_SPACE,
    /* Consumes (int) and prints some indent but only in human readable mode */
    JSON_INDENT,
    /* Prints 'null' */
    JSON_NULL,
    /* Consumes (bool) and prints either 'true' or 'false' */
    JSON_BOOLEAN,
    /* Consumes (int) and prints it as a number */
    JSON_NUMBER_INT,
    /* Consumes (const char *) and prints it as a number */
    JSON_NUMBER_STRING,
    /* Consumes (const char *) and prints it as UTF-8 string */
    JSON_STRING,
    /* Just as JSON_STRING but without the final double quotes */
    JSON_STRING_START,
    /* Just as JSON_STRING but without both initial and final double qoutes */
    JSON_STRING_NEXT,
    /* Consumes (time_t) and formats that as JSON string with strftime() format
     * of "%FT%TZ". This gives nice international timestmaps such as
     * "2012-08-13T21:15:45Z" where 'T' separates date (YYYY-MM-DD) from time
     * (HH:MM:SS) and 'Z' indicates the UTC timezone */
    JSON_TIME_STAMP,
    /* Consumes (struct timeval) and formats that as JSON string with printf()
     * "%ds %dus" where the first part contains the number of seconds and the
     * second part, number of microseconds. This format is used by LAVA to
     * express duration */
    JSON_TIME_DURATION,
    /* Just as JSON_STRING but without the initial double quotes */
    JSON_STRING_END,
};


/**
 * Flag suitable for json_format(), causes the output to be generally human readable
 **/
#define JSON_READABLE   1

/**
 * Flag suitable for json_format(), causes a newline to be printed on JSON_END
 **/
#define JSON_EOL        2


/**
 * Render a sequence of JSON tokens on to the specified json_stream.
 * The list must be terminated by JSON_END (zero).
 *
 * There are no checks for semantically valid output.
 **/
void
__attribute__((sentinel))
json_format(
    FILE *stream,
    unsigned flags, ...
    );

#endif

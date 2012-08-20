#include "json-format.h"

#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>


static
void
json_string(FILE *stream, const char *value) {
    char c;
    /* TODO: verify the string is valid UTF-8 */
    while ((c = *value++)) {
        switch (c) {
            case '"':
                fputc('\\', stream);
                fputc('"', stream);
                break;
            case '\\':
                fputc('\\', stream);
                fputc('\\', stream);
                break;
#if 0
            case '/':
                fputc('\\', stream);
                fputc('/', stream);
                break;
#endif
            case '\b':
                fputc('\\', stream);
                fputc('b', stream);
                break;
            case '\f':
                fputc('\\', stream);
                fputc('f', stream);
                break;
            case '\n':
                fputc('\\', stream);
                fputc('n', stream);
                break;
            case '\r':
                fputc('\\', stream);
                fputc('r', stream);
                break;
            case '\t':
                fputc('\\', stream);
                fputc('t', stream);
                break;
            default:
                fputc(c, stream);
                break;
        }
    }
}


void
__attribute__((sentinel))
json_format(FILE *stream, unsigned flags, ...)
{
    va_list ap;
    enum json_token token;
    va_start(ap, flags);
    do {
        token = va_arg(ap, enum json_token);
        switch (token) {
            case JSON_END:
                if (JSON_EOL & flags)
                    fputc('\n', stream);
                break;
            case JSON_DICT_START:
                fputc('{', stream);
                break;
            case JSON_DICT_END:
                fputc('}', stream);
                break;
            case JSON_ARRAY_START:
                fputc('[', stream);
                break;
            case JSON_ARRAY_END:
                fputc(']', stream);
                break;
            case JSON_COMMA:
                fputc(',', stream);
                break;
            case JSON_COLON:
                fputc(':', stream);
                break;
            case JSON_NEWLINE:
                if (JSON_READABLE & flags)
                    fputc('\n', stream);
                break;
            case JSON_SPACE:
                if (JSON_READABLE & flags)
                    fputc(' ', stream);
                break;
            case JSON_INDENT:
                {
                    int depth;
                    depth = va_arg(ap, int);
                    if (JSON_READABLE & flags)
                        while (depth-- > 0)
                            fputs("    ", stream);
                }
                break;
            case JSON_NULL:
                fputs("null", stream);
                break;
            case JSON_BOOLEAN:
                {
                    bool value;
                    value = va_arg(ap, int); /* _Bool is promoted to int when passed to ... */
                    fputs(value ? "true" : "false", stream);
                }
                break;
            case JSON_NUMBER_INT:
                {
                    int value;
                    value = va_arg(ap, int);
                    fprintf(stream, "%d", value);
                }
                break;
            case JSON_NUMBER_STRING:
                {
                    const char *value;
                    value = va_arg(ap, const char *);
                    /* TODO: verify the string is a valid number */
                    fputs(value, stream);
                }
                break;
            case JSON_STRING:
                {
                    const char *value;
                    value = va_arg(ap, const char *);
                    fputc('"', stream);
                    json_string(stream, value);
                    fputc('"', stream);
                }
                break;
            case JSON_STRING_START:
                {
                    const char *value;
                    value = va_arg(ap, const char *);
                    fputc('"', stream);
                    json_string(stream, value);
                }
                break;
            case JSON_STRING_NEXT:
                {
                    const char *value;
                    value = va_arg(ap, const char *);
                    json_string(stream, value);
                }
                break;
            case JSON_STRING_END:
                {
                    const char *value;
                    value = va_arg(ap, const char *);
                    json_string(stream, value);
                    fputc('"', stream);
                }
                break;
            case JSON_TIME_STAMP:
                {
                    time_t value;
                    struct tm tm;
                    char buf[128];
                    value = va_arg(ap, time_t);
                    gmtime_r(&value, &tm);
                    strftime(buf, sizeof buf, "%FT%TZ", &tm);
                    fputc('"', stream);
                    json_string(stream, buf);
                    fputc('"', stream);
                }
                break;
            case JSON_TIME_DURATION:
                {
                    struct timeval value;
                    const int SECONDS_IN_DAY = 60 * 60 * 24;
                    char buf[128];
                    value = va_arg(ap, struct timeval);
                    snprintf(buf, sizeof buf, "%0lldd %0llds %0lldus",
                             (long long)(value.tv_sec) / SECONDS_IN_DAY,
                             (long long)(value.tv_sec) % SECONDS_IN_DAY,
                             (long long)(value.tv_usec));
                    fputc('"', stream);
                    json_string(stream, buf);
                    fputc('"', stream);
                }
                break;
            default:
                abort();
                break;
        }
    } while (token != JSON_END);
    va_end(ap);
}

#include "bundle.h"

#include "json-format.h"


void
bundle_print_header(
    FILE *bundle_stream,
    unsigned flags,
    const char *format
    )
{
    /* This should print something like:
     *
     * <indent 0>{
     * <indent 1>"format": $format,
     * <indent 1>"test_runs": [
     */
    json_format(bundle_stream, flags,
        /* Open the bundle */
        JSON_DICT_START,
        /* Add the format field */
        JSON_NEWLINE, JSON_INDENT, 1,
            JSON_STRING, "format", JSON_COLON, JSON_SPACE,
            JSON_STRING, format, JSON_COMMA,
        /* Add the test run field */
        JSON_NEWLINE, JSON_INDENT, 1,
            JSON_STRING, "test_runs", JSON_COLON, JSON_SPACE,
            JSON_ARRAY_START,
    NULL);
}


void
bundle_print_footer(
    FILE *bundle_stream,
    unsigned flags
    )
{
    /* This should print something like:
     *
     * <indent 1>]<newline>
     * <indent 0>}<newline>
     */
    json_format(bundle_stream, flags | JSON_EOL,
        JSON_NEWLINE, JSON_INDENT, 1, JSON_ARRAY_END,
        JSON_NEWLINE, JSON_DICT_END,
    NULL);
}


void
bundle_print_test_run_header(
    FILE *bundle_stream,
    unsigned flags,
    bool comma,
    const char *analyzer_assigned_uuid,
    time_t analyzer_assigned_date,
    bool time_check_performed,
    const char *test_id
    )
{
    /* This should print something like:
     *
     * ,
     */
    if (comma)
        json_format(bundle_stream, flags, JSON_COMMA, JSON_SPACE, NULL);
    /* This should print something like:
     *
     * <indent 2>{
     * <indent 3>"analyzer_assigned_uuid": $analyzer_assigned_uuid,
     * <indent 3>"analyzer_assigned_date": $analyzer_assigned_date,
     * <indent 3>"time_check_performed": false,
     * <indent 3>"test_id": $test_id,
     * <indent 3>"test_results": [
     */
    json_format(bundle_stream, flags,
        JSON_NEWLINE, JSON_INDENT, 2, JSON_DICT_START,
        JSON_NEWLINE, JSON_INDENT, 3,
            JSON_STRING, "analyzer_assigned_uuid", JSON_COLON, JSON_SPACE,
            JSON_STRING, analyzer_assigned_uuid, JSON_COMMA,
        JSON_NEWLINE, JSON_INDENT, 3,
            JSON_STRING, "analyzer_assigned_date", JSON_COLON, JSON_SPACE,
            JSON_TIME_STAMP, analyzer_assigned_date, JSON_COMMA,
        JSON_NEWLINE, JSON_INDENT, 3,
            JSON_STRING, "time_check_performed", JSON_COLON, JSON_SPACE,
            JSON_BOOLEAN, time_check_performed, JSON_COMMA, JSON_SPACE,
        JSON_NEWLINE, JSON_INDENT, 3,
            JSON_STRING, "test_id", JSON_COLON, JSON_SPACE,
            JSON_STRING, test_id, JSON_COMMA,
        JSON_NEWLINE, JSON_INDENT, 3,
            JSON_STRING, "test_results", JSON_COLON, JSON_SPACE,
            JSON_ARRAY_START,
    NULL);
}


void
bundle_print_test_run_footer(
    FILE *bundle_stream,
    unsigned flags
    )
{
    /* This should print something like:
     *
     * <indent 3>]
     * <indent 2>}
     */
    json_format(bundle_stream, flags,
        JSON_NEWLINE, JSON_INDENT, 3, JSON_ARRAY_END,
        JSON_NEWLINE, JSON_INDENT, 2, JSON_DICT_END,
    NULL);
}


void
bundle_print_test_result_header(
    FILE *bundle_stream,
    unsigned flags,
    bool comma,
    const char *test_case_id,
    time_t timestamp
    )
{
    if (comma)
        json_format(bundle_stream, flags, JSON_COMMA, JSON_SPACE, NULL);
    /* This should print something like:
     *
     * <indent 4>{
     * <indent 5>"test_case_id": $test_case_id,
     * <indent 5>"timestamp": $timestamp,
     * <indent 5>"message": "
     *
     * note: the message value (string) is _not_ terminated
     */
    json_format(bundle_stream, flags,
        JSON_NEWLINE, JSON_INDENT, 4, JSON_DICT_START,
        JSON_NEWLINE, JSON_INDENT, 5,
            JSON_STRING, "test_case_id", JSON_COLON, JSON_SPACE,
            JSON_STRING, test_case_id, JSON_COMMA,
        JSON_NEWLINE, JSON_INDENT, 5,
            JSON_STRING, "timestamp", JSON_COLON, JSON_SPACE,
            JSON_TIME_STAMP, timestamp, JSON_COMMA,
        JSON_NEWLINE, JSON_INDENT, 5,
            JSON_STRING, "message", JSON_COLON, JSON_SPACE,
            JSON_STRING_START, "",
    NULL);
}



void
bundle_print_test_result_message(
    FILE *bundle_stream,
    unsigned flags,
    const char *message
    )
{
    json_format(bundle_stream, flags,
        JSON_STRING_NEXT, message,
        JSON_STRING_NEXT, "\n", NULL);
}


void
bundle_print_test_result_footer(
    FILE *bundle_stream,
    unsigned flags,
    const char *result,
    const char *log_filename,
    int log_lineno,
    struct timeval duration
    )
{
    /* This should print something like:
     *
     * ",
     * <indent 5>"result": $result,
     * <indent 5>"duration": $duration,
     * <indent 5>"log_filename": $log_filename,
     * <indent 5>"log_lineno": $log_lineno,
     * <indent 4>}
     *
     * note: the first part terminates the quote left open by bundle_print_test_result_header()
     */
    json_format(bundle_stream, flags,
        JSON_STRING_END, "", JSON_COMMA,
        JSON_NEWLINE, JSON_INDENT, 5,
            JSON_STRING, "result", JSON_COLON, JSON_SPACE,
            JSON_STRING, result, JSON_COMMA,
        JSON_NEWLINE, JSON_INDENT, 5,
            JSON_STRING, "duration", JSON_COLON, JSON_SPACE,
            JSON_TIME_DURATION, duration, JSON_COMMA,
        JSON_NEWLINE, JSON_INDENT, 5,
            JSON_STRING, "log_filename", JSON_COLON, JSON_SPACE,
            JSON_STRING, log_filename, JSON_COMMA,
        JSON_NEWLINE, JSON_INDENT, 5,
            JSON_STRING, "log_lineno", JSON_COLON, JSON_SPACE,
            JSON_NUMBER_INT, log_lineno,
        JSON_NEWLINE, JSON_INDENT, 4, JSON_DICT_END,
    NULL);
}

#ifndef BUNDLE_H
#define BUNDLE_H

/**
 * Utility functions for printing Linaro Dashboard Bundles.
 * See http://linaro-dashboard-bundle.readthedocs.org/en/latest/schema/examples.html
 * for example bundles.
 **/

#include <stdbool.h>
#include <stdio.h>
#include <sys/time.h>
#include <time.h>

/**
 * Print the header of a bundle object.
 *
 * Must be called in pair with bundle_print_footer().
 *
 * Once called you may call bundle_print_test_run_header().
 **/
void
bundle_print_header(
    FILE *bundle_stream,
    unsigned flags,
    const char *format
    );


/**
 * Print the footer of a bundle object.
 *
 * Terminates a complete bundle. You cannot call any other bundle_print_*
 * functions on the same stream after that or the bundle will be incorrect
 * JSON.
 **/
void
bundle_print_footer(
    FILE *bundle_stream,
    unsigned flags
    );


/**
 * Prints the header of a test run object.
 *
 * Must be called in pair with bundle_print_test_run_footer().
 *
 * Once called you may call bundle_print_test_result_header().
 **/
void
bundle_print_test_run_header(
    FILE *bundle_stream,
    unsigned flags,
    bool comma,
    const char *analyzer_assigned_uuid,
    time_t analyzer_assigned_date,
    bool time_check_performed,
    const char *test_id
    );


/**
 * Prints the footer of a test run object.
 *
 * Must be called in pair with bundle_print_test_run_header().
 *
 * Once called you may call bundle_print_test_result_header().
 **/
void
bundle_print_test_run_footer(
    FILE *bundle_stream,
    unsigned flags
    );

/**
 * Prints the header of a test result object.
 *
 * Must be called in pair with bundle_print_test_result_footer().
 *
 * The initial call in the current test_run must pass comma=false, all
 * subsequent calls must pass true there.
 *
 * When called you may call bundle_print_test_result_message() (any number of times)
 **/
void
bundle_print_test_result_header(
    FILE *bundle_stream,
    unsigned flags,
    bool comma,
    const char *test_case_id,
    time_t timestamp
    );


/**
 * Prints a (fragment of) test result message.
 *
 * May be called between bundle_print_test_result_header() and
 * bundle_print_test_result_footer().
 *
 * May be called multiple times. Each time the 'message' is directly
 * concatenated to any previous messages.
 **/
void
bundle_print_test_result_message(
    FILE *bundle_stream,
    unsigned flags,
    const char *message
    );


/**
 * Prints the footer of a test result.
 *
 * Must be called in pair with bundle_print_test_result_header().
 **/
void
bundle_print_test_result_footer(
    FILE *bundle_stream,
    unsigned flags,
    const char *result,
    const char *log_filename,
    int log_lineno,
    struct timeval duration
    );


#endif

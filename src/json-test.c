#include "json-test.h"

#include "json-format.h"

#include <limits.h>
#include <stdbool.h>
#include <stdio.h>

#define MSG_INFO    "[==========] "
#define MSG_DEBUG   "[----------] "


#define TEST_HEADER() printf(MSG_INFO "Output of: %s\n", __FUNCTION__)
#define TEST_NEXT() printf("\n" MSG_DEBUG "Additional line of output\n")
#define TEST_FOOTER() printf("\n" MSG_DEBUG "(end of test case)\n")


static void test_nothing() {
    TEST_HEADER();
    json_format(stdout, 0, NULL);
    TEST_FOOTER();
}


static void test_dict() {
    TEST_HEADER();
    json_format(stdout, 0, JSON_DICT_START, JSON_COLON, JSON_DICT_END, NULL);
    TEST_FOOTER();
}


static void test_array() {
    TEST_HEADER();
    json_format(stdout, 0, JSON_ARRAY_START, JSON_COMMA, JSON_ARRAY_END, NULL);
    TEST_FOOTER();
}


static void test_null() {
    TEST_HEADER();
    json_format(stdout, 0, JSON_NULL, NULL);
    TEST_FOOTER();
}


static void test_bool() {
    TEST_HEADER();
    json_format(stdout, 0, JSON_BOOLEAN, true, NULL);
    TEST_NEXT();
    json_format(stdout, 0, JSON_BOOLEAN, false, NULL);
    TEST_FOOTER();
}


static void test_int() {
    TEST_HEADER();
    json_format(stdout, 0, JSON_NUMBER_INT, 0, NULL);
    TEST_NEXT();
    json_format(stdout, 0, JSON_NUMBER_INT, INT_MAX, NULL);
    TEST_NEXT();
    json_format(stdout, 0, JSON_NUMBER_INT, INT_MIN, NULL);
    TEST_FOOTER();
}


static void test_int_str() {
    TEST_HEADER();
    json_format(stdout, 0, JSON_NUMBER_STRING, "0", NULL);
    TEST_NEXT();
    json_format(stdout, 0, JSON_NUMBER_STRING, "15.2", NULL);
    TEST_FOOTER();
}


static void test_str() {
    TEST_HEADER();
    json_format(stdout, 0, JSON_STRING, "hello world", NULL);
    TEST_NEXT();
    json_format(stdout, 0, JSON_STRING, "double quote:   \"", NULL);
    TEST_NEXT();
    json_format(stdout, 0, JSON_STRING, "forward slash:  \\", NULL);
    TEST_NEXT();
    json_format(stdout, 0, JSON_STRING, "backspace:      \b", NULL);
    TEST_NEXT();
    json_format(stdout, 0, JSON_STRING, "form feed:      \f", NULL);
    TEST_NEXT();
    json_format(stdout, 0, JSON_STRING, "new line:       \n", NULL);
    TEST_NEXT();
    json_format(stdout, 0, JSON_STRING, "carriage return:\r", NULL);
    TEST_NEXT();
    json_format(stdout, 0, JSON_STRING, "tab:            \t", NULL);
    TEST_NEXT();
    json_format(stdout, 0, JSON_STRING, "single quote:   ' (should be UNQUOTED)", NULL);
    TEST_NEXT();
    json_format(stdout, 0, JSON_STRING, "", NULL);
    TEST_NEXT();
    json_format(stdout, 0, JSON_STRING, "0", NULL);
    TEST_FOOTER();
}


void json_test_all() {
    test_nothing();
    test_dict();
    test_array();
    test_null();
    test_bool();
    test_int();
    test_int_str();
    test_str();
}

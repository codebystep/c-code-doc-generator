/**
 * Module utility.c
 * This module contains the definitions of utility functions declared in utility.h.
 * The functions here are primarily used for basic string operations like trimming,
 * which are essential for processing and preparing strings for further actions in the program.
 */

#include "utility.h"
#include <string.h>
#include <ctype.h>

/**
 * Trims leading and trailing whitespace from a string.
 * This function takes an input string and produces a new string with all leading and trailing
 * whitespace removed. It's useful for cleaning up user input or formatting strings before display or further processing.
 * @param input The string to be trimmed.
 * @param output The trimmed string output.
 */
void trimLine(const char *input, char *output) {
    const char *start = input;
    /* Skip leading whitespace */
    while (isspace((unsigned char)*start)) {
        start++;
    }

    /* Find the end of the string, skipping trailing whitespace */
    const char *end = input + strlen(input) - 1;
    while (end > start && isspace((unsigned char)*end)) {
        end--;
    }

    /* Copy the trimmed portion to the output */
    strncpy(output, start, end - start + 1);
    output[end - start + 1] = '\0';
}

/*

strop.c

String operation functions.

Part of the "Lightning-Fast Password Check" project by OperaVaria.

*/

// Header files:
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "strop.h"

/* Copy a substring to a manually allocated char array.
The substring is delimited by two pointers passed as arguments.
Returns pointer to substring, error returns NULL value.
Memory must be freed! */
char *copy_substring(const char *start, const char *end) {

    // Error handling for invalid pointers.
    if (start == NULL || end == NULL || start > end) {
        return NULL;
    }

    // Calculate the length of the substring.
    size_t length = end - start;

    // Allocate memory for the substring + error handling.
    char *substring = (char *)malloc((length + 1) * sizeof(char));
    if (substring == NULL) {
        return NULL;
    }

    // Copy the substring.
    strncpy(substring, start, length);

    // Null-terminate the substring.
    substring[length] = '\0';

    return substring;
}

/* Function to handle the haveibeenpwned.com response string.
Takes the response string and a password hash suffix as arguments.
Returns the number the password has been in a data breach (as long int). */
long int haveibeenpwned_res_hand(const char *response, const char *suffix) {

    // Declare return variable.
    long int pwn_num;

    //Search for suffix in response string.
    char *line_ptr = strstr(response, suffix);

    if (line_ptr != NULL) {

        /* If found, set pointers to the start and end
        of the pwn number. */
        char *start_ptr = strchr(line_ptr, ':');
        char *end_ptr = strchr(line_ptr, '\r');
        start_ptr++; // Move pointer over ':'.

        // Convert numbers to long int.
        pwn_num = strtol(start_ptr, &end_ptr, 10);

    }
    else {
        // Not found: set to 0.
        pwn_num = 0;
    }

    return pwn_num;
}

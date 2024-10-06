/*

strop.c

String operation functions.

Part of the "Lightning-Fast Password Check" project by OperaVaria.

*/

// Header files:
#include <stdlib.h>
#include <string.h>
#include "strop.h"

/* Copy a substring to a manually allocated char array.
The substring is delimited by two pointer passed as arguments.
Returns pointer to substring. */
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
Takes the response string and a password suffix hash as arguments.
Returns the number the hash turns up in the database. */
char *haveibeenpwned_res_hand(const char *response, const char *suffix) {

    // Declare return pointer.
    char *pwn_num;

    //Search for suffix in response string.
    char *line_ptr = strstr(response, suffix);	
        
    if (line_ptr != NULL) {

        /* If found, set pointers to the start and end
        of the pwn count number. */ 
        char *start_ptr = strchr(line_ptr, ':');
        char *end_ptr = strchr(line_ptr, '\r');        
        start_ptr++; // Move pointer over ':'.

        // Call substring copy function.
        pwn_num = copy_substring(start_ptr, end_ptr);
        
    } 
    else {
        // Not found: set return variable to null.
        pwn_num = NULL;
    }

    return pwn_num;
}

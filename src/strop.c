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
    size_t length = end - start + 1;

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

/* Custom fgets-like function: retrieves and stores input from
a stream to a character array. */
char *get_input(char *output_str, size_t arr_length, FILE *input_stream)
{
    // Declare variables.
    char ch;
    int i = 0;
    int l = arr_length--;

    // Read and store input until newline or endfile character encountered.
    while ((ch = getc(input_stream)) != '\n' && ch != EOF)
    {
        // If arr_length too short: error message, clear input buffer.
        if (l == i)
        {
            fprintf(stderr, "Warning: input too long. String truncated.\n");
            while ((ch = getchar()) != '\n' && ch != EOF) { }
            break;
        }
        // Else: normal operation (add to array, increment iterator).
        else
        {
            output_str[i] = ch;
            i++;
        }
    }

    // Add null terminator to end of string.
    output_str[i] = '\0';

    return output_str;
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
        start_ptr++;
        end_ptr--;

        // Call substring copy function.
        pwn_num = copy_substring(start_ptr, end_ptr);
    } 
    else {
        // Not found: set return variable to null.
        pwn_num = NULL;
    }

    return pwn_num;
}

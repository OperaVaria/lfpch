/*

backend.c

Functions related to backend processes.

Part of the "Lightning-Fast Password Check" project by OperaVaria.

*/

// Header files.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "backend.h"
#include "hashing.h"
#include "macros.h"
#include "request.h"
#include "types.h"

/* Processes backend function calls. Takes a Password struct instance as argument,
fills it with proper values. */ 
void backend_process(Password *password_ptr) {   
        
    /* HASHING */

    // Call hashing functions.
    generate_sha1(password_ptr->pass_data, password_ptr->digest);
    convert_digest(password_ptr->digest, password_ptr->digest_str);
    split_digest_str(password_ptr->digest_str, password_ptr->prefix, password_ptr->suffix);

    /* REQUEST */

    // Build request url.
    char url[64];
    sprintf(url, "https://api.pwnedpasswords.com/range/%s", password_ptr->prefix);

    // Create Memory struct instance to store response chunks.
    Memory memory;
    memory.string = malloc(1);
    memory.size = 0;

    // Call cURL session function.
    curl_session(url, &memory);

    // Call response handling function to get pwn number, store it in struct.
    password_ptr->pwn_num = haveibeenpwned_res_hand(memory.string, password_ptr->suffix);

    // Free response string memory.
    free(memory.string);
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

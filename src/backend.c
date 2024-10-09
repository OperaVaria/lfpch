/*

backend.c

Functions related to backend processes.

Part of the "Lightning-Fast Password Check" project by OperaVaria.

*/

// Header files.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "backend.h"
#include "hashing.h"
#include "request.h"
#include "types.h"

/* Processes backend function calls to check the number of
leaked data breaches the password was part of. Uses the
haveibeenpwned.com password API. Takes a Password struct pointer
as argument, fills it with proper values. */ 
void password_check_process(Password *password_ptr) {   
        
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

    // Call cURL session function with error handling.
    int curl_response = curl_session(url, &memory) != 0;
    if (curl_response != 0) {
        fprintf(stderr, "cURL error, code: %d, exiting app.\n", curl_response);
        exit(EXIT_FAILURE);
    }

    // Call response handling function to get pwn number, store it in struct.
    password_ptr->pwn_num = haveibeenpwned_res_hand(memory.string, password_ptr->suffix);

    // Free response string memory allocated in write_chunk_cb().
    free(memory.string);
}

/* Function to handle a haveibeenpwned.com response string.
Takes the response string and a password hash suffix as arguments.
Returns the number the password has been in a data breach according to the
website database (as long int). */
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

/* Random password generator function. Takes the password
length and an output array pointer as argument. */ 
void password_generator(size_t length, char *password) {

    // String literals for character types:

    char digits[] = "0123456789";
    int digits_length = strlen(digits);

    char lowers[] = "abcdefghijklmnopqrstuwxyz";
    int lowers_length = strlen(lowers);

    char uppers[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    int uppers_length = strlen(uppers);

    char symbols[] = "!@#$%^&*()";
    int symbols_length = strlen(symbols);

    // Set the seed (UNIX epoch time).
    srand(time(NULL));

    // Loop to get a random character one-by-one.
    for (int i = 0; i < length; i++) {
        
        // Chose type randomly with rand() and a switch.
        int char_type = rand() % 4;

        /* After random type selection: random character
        selection from a "type" array. */
        switch (char_type) {
        case 0: // Random digit
            password[i] = digits[rand() % digits_length];
            break;
        case 1: // Random lower case letter.
            password[i] = lowers[rand() % lowers_length];
            break;
        case 2: // Random upper case letter.
            password[i] = uppers[rand() % uppers_length];
            break;
        case 3: // Random symbol.
            password[i] = symbols[rand() % symbols_length];
            break;
        default: // Invalid selection.
            fprintf(stderr, "Selection error in the random generator!");
            exit(EXIT_FAILURE);
        }
    }

    // Null terminate the array.
    password[length] = '\0';
}

/*

backend.c

Functions related to backend processes.

Part of the "Lightning-Fast Password Check" project by OperaVaria.

*/

// Header files.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <immintrin.h>
#include "backend.h"
#include "hashing.h"
#include "request.h"
#include "types.h"

/* Processes backend function calls to check the number of
leaked data breaches the password was part of. Uses the
haveibeenpwned.com password API. Takes a Password struct pointer
as argument, fills the stuct with proper values. */
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

    /* Declare header string. Adds padding to the haveibeenpwned.com response
    for more obfuscation. */
    char header_data[] = "Add-Padding: true";

    // Create Memory struct instance to store response chunks.
    Memory memory;
    memory.string = malloc(1);
    memory.size = 0;

    // Call cURL session function with error handling.
    int curl_response = curl_session(url, header_data, &memory);
    if (curl_response != 0) {
        fprintf(stderr, "cURL error, code: %d, exiting app.\n", curl_response);
        exit(EXIT_FAILURE);
    }

    // Call response handling function to get pwn number. Store it in struct.
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

/* Random password generator function.
Takes password attributes (length, character types to include)
as arguments + array pointer to store the password. */
void password_generator(size_t password_length, char *password,
                        bool lower_include, bool upper_include,
                        bool num_include, bool symbol_include) {

    // Declare variables.
    char charset[256] = "";
    size_t charset_length = 0;

    /* Add to the character set the selected character types
    and their length. */
    if (lower_include) {
        const char lowercase[] = "abcdefghijklmnopqrstuvwxyz";
        strcat(charset, lowercase);
        charset_length += strlen(lowercase);
    }
    if (upper_include) {
        const char uppercase[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
        strcat(charset, uppercase);
        charset_length += strlen(uppercase);
    }
    if (num_include) { // Digits added twice to compensate for str length.
        const char numbers[] = "01234567890123456789";
        strcat(charset, numbers);
        charset_length += strlen(numbers);
    }
    if (symbol_include) {
        const char symbols[] = "!@#$%^&*()_+-=[]{}|;:,.<>?";
        strcat(charset, symbols);
        charset_length += strlen(symbols);
    }

    // Set a "true" random seed for rand(). Source: x86 processor's DRNG.
    srand(get_random_seed());

    // Loop to fill the output array one-by-one with random characters.
    for (size_t i = 0; i < password_length; i++) {
        password[i] = charset[rand() % charset_length];
    }

    // Null terminate the array.
    password[password_length] = '\0';
}

/* Generate a "true" random seed with an x86 processor's DRNG.
Returns random number as unsigned int. */
unsigned int get_random_seed() {

    // Declare variables.
    int tries = 0;
    int status;
    unsigned int result;

    /* Get random integer with the RDSEED instruction,
    retry if it fails (failure = 0), retry max 100 times. */
    do {
        status = _rdseed32_step(&result);
        tries++;
    } while (status != 1 && tries <= 100);

    // If the call still fails: serious error, exit program.
    if (status == 0) {
        fprintf(stderr, "CPU error, random number generation failed.\n");
        exit(EXIT_FAILURE);
    }

    return result;
}

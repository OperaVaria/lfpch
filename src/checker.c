/*

checker.c

Functions related to password checking backend processes.

Part of the "Lightning-Fast Password Check" project by OperaVaria.

*/

// Header files.
#include <ctype.h>
#include "checker.h"
#include "hashing.h"
#include "macros.h"
#include "request.h"
#include "types.h"

// Static function prototypes.
static long int haveibeenpwned_res_hand(const char *response, const char *suffix);

/* Processes backend function calls to check the number of
leaked data breaches the password was part of. Uses the
haveibeenpwned.com password API. Takes a Password struct pointer
as argument, returns the "pwn" count converted to a (long) int. */
long int pwn_check_process(Password *password_ptr) {
    
    /* HASHING */

    // Call hashing functions.
    generate_sha1(password_ptr->input_data, password_ptr->digest);
    convert_digest(password_ptr->digest, password_ptr->digest_str);
    split_digest_str(password_ptr->digest_str, password_ptr->prefix, password_ptr->suffix);

    /* REQUEST */

    // Declare variables.
    char url[64];
    int curl_response; 
    long int pwn_num;

    // Build request url.
    sprintf(url, "https://api.pwnedpasswords.com/range/%s", password_ptr->prefix);

    /* Declare header string. Adds padding to the haveibeenpwned.com response
    for more obfuscation. */
    char header_data[] = "Add-Padding: true";

    // Create Memory struct instance to store response chunks.
    Memory memory;
    memory.string = malloc(1);
    memory.size = 0;

    // Call cURL session function with error handling.
    curl_response = curl_session(url, header_data, &memory);
    if (curl_response != 0) {
        fprintf(stderr, "cURL error, code: %d, exiting app.\n", curl_response);
        exit(EXIT_FAILURE);
    }

    // Call response handling function to get pwn number.
    pwn_num = haveibeenpwned_res_hand(memory.string, password_ptr->suffix);

    // Free response string memory allocated in write_chunk_cb().
    free(memory.string);

    return pwn_num;
}

/* Function to handle a haveibeenpwned.com response string.
Takes the response string and a password hash suffix as arguments.
Returns the number the password has been in a data breach according to the
website's database (as long int). */
static long int haveibeenpwned_res_hand(const char *response, const char *suffix) {

    // Declare variables.
    char *line_ptr, *start_ptr, *end_ptr;
    long int pwn_num;

    //Search for suffix in response string.
    line_ptr = strstr(response, suffix);

    if (line_ptr != NULL) {

        /* If found, set pointers to the start and end
        of the pwn number. Line format: suffix:number\r\n */
        start_ptr = strchr(line_ptr, ':');
        end_ptr = strchr(line_ptr, '\r');
        start_ptr++; // Move pointer over ':'.

        // Convert number character(s) to long int.
        pwn_num = strtol(start_ptr, &end_ptr, 10);

    }
    else {
        // Not found: set to 0.
        pwn_num = 0;
    }

    return pwn_num;
}

/* Function to calculate password strength. Scores between 0-100 based on
length and character type variety. Takes the password and its length as
arguments, returns the score. */
int password_strength_check(const char* password, size_t length) {

    // Initialize variables.
    int score = 0, lowercase_count = 0, uppercase_count = 0,
        number_count = 0, symbol_count = 0;

    // Length score (40 points).
    score += (length >= STRONG_PASSWORD_LENGTH) ? 40 : (length * 40 / STRONG_PASSWORD_LENGTH);

    // Calculate character type variety.
    for (size_t i = 0; i < length; i++) {
        if (islower(password[i])) lowercase_count++;
        else if (isupper(password[i])) uppercase_count++;
        else if (isdigit(password[i])) number_count++;
        else symbol_count++;
    }

    // Calculate character variety score (60 points).
    score += (uppercase_count > 0) * 10;
    score += (lowercase_count > 0) * 10;
    score += (number_count > 0) * 20;
    score += (symbol_count > 0) * 20;

    // Penalty if password shorter than minimum recommended length.
    if (length < PASSWORD_MIN_LENGTH) {
        score = score * length / PASSWORD_MIN_LENGTH;
    }
    
    // Return a score no higher than 100.
    return (score > 100) ? 100 : score;
}

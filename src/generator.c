/*

generator.c

Functions related to the password generating backend process.

Part of the "Lightning-Fast Password Check" project by OperaVaria.

*/

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <immintrin.h>
#include "generator.h"

// Static function prototypes.
static unsigned int get_random_seed();

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
static unsigned int get_random_seed() {

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

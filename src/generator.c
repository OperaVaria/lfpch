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
as arguments + char array pointer to store the password. */
void password_generator(char *password, size_t password_length,
                        bool lower_include, bool upper_include,
                        bool num_include, bool symbol_include) {
    
    // Declare charset constants.
    const char lowercase[] = "abcdefghijklmnopqrstuvwxyz";
    const char uppercase[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    const char numbers[] = "0123456789";
    const char symbols[] = "!@#$%^&*()_+-=[]{}|;:,.<>?";

    // Create arrays of charset pointers, length values, and include booleans.
    const char* charsets[4] = {lowercase, uppercase, numbers, symbols};
    size_t charset_lengths[4] = {strlen(lowercase), strlen(uppercase), strlen(numbers), strlen(symbols)};
    bool charset_include[4] = {lower_include, upper_include, num_include, symbol_include};

    // Set a "true" random seed for rand(). Source: x86 processor's DRNG.
    srand(get_random_seed());

    // Loop to fill the output array one-by-one with random characters.
    for (int i = 0; i < password_length; i++) {

        // Randomly select a character type (only if marked as included).
        int charset_index;
        do {
            charset_index = rand() % 4;
        } while (!charset_include[charset_index]);

        // Select a random character from the chosen character set
        int char_index = rand() % charset_lengths[charset_index];
        password[i] = charsets[charset_index][char_index];
    }

    // Null terminate the array.
    password[password_length] = '\0';

    /* Randomly swap in a character from every selected 
    char type to ensure all are present. */
    for (int i = 0; i < 4; i++) {
        if (charset_include[i]) {
            int replace_index = rand() % password_length;
            int char_index = rand() % charset_lengths[i];
            password[replace_index] = charsets[i][char_index];
        }
    }
}

/* Generate a "true" random seed with the x86 processor's DRNG.
Returns random number as unsigned int. */
static unsigned int get_random_seed() {

    // Declare variables.
    int status, tries = 0;
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

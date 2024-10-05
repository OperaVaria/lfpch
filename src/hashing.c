/*

hashing.c

Functions related to password hashing and hash handling.

Part of the "Lightning-Fast Password Check" project by OperaVaria.

*/

// Header files.
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <openssl/sha.h>
#include "hashing.h"
#include "macros.h"

/* Generates and stores an SHA-1 digest from input data.
Uses the OpenSSL SHA-1 function (macro). */
void generate_sha1(const char *data, unsigned char *digest) {

    // Get string length.
    size_t length = strlen(data);

    // Convert input array to unsigned.
    unsigned char unsigned_data[length];
    for (int i = 0; i < length; i++) {
        unsigned_data[i] = (unsigned char)data[i];
    }
    
    // Hash.
    SHA1(unsigned_data, length, digest);
}

/* Creates a string from an unsigned char hex array. Format: two digit,
capitalized. */
void convert_digest(const unsigned char *hex_arr, char *output_arr) {
    for (int i = 0; i < SHA_DIGEST_LENGTH; i++) {
        sprintf(output_arr + i*2, "%02X", hex_arr[i]);
    }
    output_arr[SHA_DIGEST_LENGTH*2] = '\0';
}

/* Splits an copies digest string into a prefix (first 5 characters)
and a suffix (remaining) array. Needed for the haveibeenpwned.com password API. */
void split_digest_str(const char *digest, char *prefix, char *suffix) {
    for (int i = 0; i < SHA_DIGEST_LENGTH*2; i++) {

        // Add first five characters to prefix array.
        if (i < 5) {
            prefix[i] = digest[i];
        }
        
        // Add null terminator to prefix string.
        else if (i == 5) {
            prefix[i] = '\0';
        }
        
        // Copy rest to suffix array.
        else {
            suffix[i - PREFIX_LENGTH] = digest[i];
        }
    }
}

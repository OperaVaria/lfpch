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
    size_t length = strlen(data);
    SHA1((const unsigned char *)data, length, digest);
}

/* Creates a string from an unsigned char hex array. Format: two digit,
capitalized. */
void convert_digest(const unsigned char *hex_arr, char *output_arr) {
    for (int i = 0; i < SHA_DIGEST_LENGTH; i++) {
        snprintf(output_arr + i*2, 3, "%02X", hex_arr[i]);
    }
    output_arr[SHA_DIGEST_LENGTH*2] = '\0';
}

/* Splits an copies digest string into a prefix (first 5 characters)
and a suffix (remaining) array. Needed for the haveibeenpwned.com password API. */
void split_digest_str(const char *digest, char *prefix, char *suffix) {
    
    // Copy first 5 characters into prefix.
    strncpy(prefix, digest, 5);
    prefix[5] = '\0';

    // Copy the remaining characters into suffix.
    strcpy(suffix, digest + 5);
}

/*

hashing.c

Functions related to password hashing and hash handling.

All functions use a Password stuct instance to retrieve and save data
that is defined in "types.h".


Part of the "Lightning-Fast Password Check" project by OperaVaria.

*/

// Header files.
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <openssl/sha.h>
#include "hashing.h"

/* Generates and stores SHA-1 digest from password data.
Uses the OpenSSL SHA-1 function to create the hash. */
void generate_sha1(Password *struct_ptr) {
    size_t length = strlen(struct_ptr->data);
    SHA1(struct_ptr->data, length, struct_ptr->digest);
}

// Creates a string form the unsigned char hex array.
void convert_digest(Password *struct_ptr) {
    for (int i = 0; i < SHA_DIGEST_LENGTH; i++) {
        sprintf(struct_ptr->digest_str + i*2, "%02x", struct_ptr->digest[i]);
    }
    struct_ptr->digest_str[SHA_DIGEST_LENGTH*2] = '\0';
}

/* Splits the digest string into a prefix (first 5 characters) and
a suffix (remaining) and stores them. All characters are capitalized.
Implemented with a simple for loop. */
void split_digest_str(Password *struct_ptr) {
    for (int j = 0; j < SHA_DIGEST_LENGTH*2; j++) {
        
        // Convert letters to upper case.         
        struct_ptr->digest_str[j] = toupper(struct_ptr->digest_str[j]);

        // Add first five characters to prefix array.
        if (j < 5) {
            struct_ptr->prefix[j] = struct_ptr->digest_str[j];
        }
        
        // Add null terminator to prefix string.
        else if (j == 5) {
            struct_ptr->prefix[j] = '\0';
        }
        
        // Copy rest to suffix array.
        else {
            struct_ptr->suffix[j - PREFIX_LENGTH] = struct_ptr->digest_str[j];
        }
    }
}



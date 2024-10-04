/*

types.h

Header file containing custom types.

Part of the "Lightning-Fast Password Check" project by OperaVaria.

*/

// Guard.
#ifndef TYPES_H
#define TYPES_H

// Header files.
#include <openssl/sha.h>
#include "macros.h"

/* Memory location for a string.
Mainly used by the cURL callback function. */
typedef struct Memory {
    char *string;
    size_t size;
} Memory;

// Struct to store all password data needed.
typedef struct Password {
    char data[PASSWORD_MAX_LENGTH];
    unsigned char digest[SHA_DIGEST_LENGTH];
    char digest_str[DIGEST_STRING_LENGTH];
    char prefix[PREFIX_LENGTH];
    char suffix[SUFFIX_LENGTH];
    char *pwn_num;
} Password;

#endif

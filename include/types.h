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

typedef struct Memory {
    char *res_str;
    size_t size;
} Memory;

typedef struct Password {
    char data[PASSWORD_MAX_LENGTH];
    unsigned char digest[SHA_DIGEST_LENGTH];
    char digest_str[DIGEST_STRING_LENGTH];
    char prefix[PREFIX_LENGTH];
    char suffix[SUFFIX_LENGTH];

} Password;

#endif

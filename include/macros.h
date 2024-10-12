/*

macros.h

Header file containing global preprocessor constants and macros.

Part of the "Lightning-Fast Password Check" project by OperaVaria.

*/

// Guard.
#ifndef MACROS_H
#define MACROS_H

// Header files.
#include <openssl/sha.h>

// Constants.
#define DIGEST_STRING_LENGTH SHA_DIGEST_LENGTH * 2 + 1
#define PREFIX_LENGTH 6
#define SUFFIX_LENGTH DIGEST_STRING_LENGTH - 5
#define PASSWORD_MAX_LENGTH 64
#define PASSWORD_MIN_LENGTH 8
#define STRONG_PASSWORD_LENGTH 16

#endif

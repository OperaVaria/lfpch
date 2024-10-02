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

typedef struct Password
{
    char data[PASSWORD_MAX_LENGTH];
	unsigned char digest[SHA_DIGEST_LENGTH];
	unsigned char first_five[5];
	
} Password;

#endif

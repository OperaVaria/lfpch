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

typedef struct Password {
    char data[64];
	unsigned char digest[SHA_DIGEST_LENGTH];
    char digest_str[SHA_DIGEST_LENGTH*2+1];
	char prefix[6];
    char suffix[36];
	
} Password;

#endif

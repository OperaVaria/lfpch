/*

hashing.h

Header file for hashing.c.

Part of the "Lightning-Fast Password Check" project by OperaVaria.

*/

// Guard.
#ifndef HASHING_H
#define HASHING_H

// Header files.
#include "types.h"

// Function prototypes.
void generate_sha1(Password *struct_ptr);
void convert_digest(Password *struct_ptr);
void split_digest_str(Password *struct_ptr);

#endif

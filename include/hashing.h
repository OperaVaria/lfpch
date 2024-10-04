/*

hashing.h

Header file for hashing.c.

Part of the "Lightning-Fast Password Check" project by OperaVaria.

*/

// Guard.
#ifndef HASHING_H
#define HASHING_H

// Function prototypes.
void generate_sha1(const char *password, unsigned char *digest);
void convert_digest(unsigned char *hex_arr, char *output_str);
void split_digest_str(const char *digest, char *prefix, char *suffix);

#endif

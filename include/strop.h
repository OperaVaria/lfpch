/*

strop.h

Header file for strop.c.

Part of the "Lightning-Fast Password Check" project by OperaVaria.

*/

// Guard.
#ifndef STROP_H
#define STROP_H

// Header files.
#include <stdio.h>

// Function prototypes.
char *copy_substring(const char *start, const char *end);
long int haveibeenpwned_res_hand(const char *response, const char *suffix);

#endif

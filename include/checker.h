/*

checker.h

Header file for checker.c.

Part of the "Lightning-Fast Password Check" project by OperaVaria.

*/

// Guard.
#ifndef CHECKER_H
#define CHECKER_H

// Header files.
#include <stddef.h>
#include "types.h"

// Function prototypes.
long int pwn_check_process(Password *password);
int password_strength_check(const char* password, size_t length);

#endif

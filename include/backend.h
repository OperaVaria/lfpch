/*

backend.h

Header file for backend.c.

Part of the "Lightning-Fast Password Check" project by OperaVaria.

*/

// Guard.
#ifndef BACKEND_H
#define BACKEND_H

// Header files.
#include "types.h"

// Function prototypes.
void password_check_process(Password *password);
void password_generator(size_t length, char *password);
long int haveibeenpwned_res_hand(const char *response, const char *suffix);

#endif

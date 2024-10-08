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
long int haveibeenpwned_res_hand(const char *response, const char *suffix);
void password_generator(size_t password_length, char *password,
                        bool lower_include, bool upper_include,
                        bool num_include, bool symbol_include);
unsigned int get_random_seed();

#endif

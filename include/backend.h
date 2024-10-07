/*

backend.h

Header file for gui.h.

Part of the "Lightning-Fast Password Check" project by OperaVaria.

*/

// Guard.
#ifndef BACKEND_H
#define BACKEND_H

// Header files.
#include "types.h"

// Function prototypes.
void backend_process(Password *password);
long int haveibeenpwned_res_hand(const char *response, const char *suffix);

#endif

/*

requests.h

Header file for requests.c.

Part of the "Lightning-Fast Password Check" project by OperaVaria.

*/

// Guard.
#ifndef REQUESTS_H
#define REQUESTS_H

// Header files.
#include "types.h"

// Function prototypes.
int curl_session(const char *url, Memory *struct_ptr);

#endif

/*

request.h

Header file for request.c.

Part of the "Lightning-Fast Password Check" project by OperaVaria.

*/

// Guard.
#ifndef REQUEST_H
#define REQUEST_H

// Header files.
#include "types.h"

// Function prototypes.
int curl_session(const char *url, const char *custom_header, Memory *memory_ptr);

#endif

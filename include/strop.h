/*

strop.h

Header file for strop.c.

Part of the "Lightning-Fast Password Check" project by OperaVaria.

*/

// Guard.
#ifndef strop_H
#define strop_H

// Header files.
#include <stdio.h>

// Function prototypes.
char *copy_substring(const char *start, const char *end);
char *get_input(char *output_str, size_t arr_length, FILE *input_stream);

#endif

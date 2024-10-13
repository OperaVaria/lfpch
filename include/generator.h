/*

generator.h

Header file for generator.c.

Part of the "Lightning-Fast Password Check" project by OperaVaria.

*/

// Guard.
#ifndef GENERATOR_H
#define GENERATOR_H

// Header files.
#include <stddef.h>
#include <stdbool.h>

// Function prototypes.
void password_generator(char *password, size_t password_length,
                        bool lower_include, bool upper_include,
                        bool num_include, bool symbol_include);

#endif

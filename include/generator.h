/*

generator.h

Header file for generator.c.

Part of the "Lightning-Fast Password Check" project by OperaVaria.

*/

// Guard.
#ifndef GENERATOR_H
#define GENERATOR_H

// Header files.
#include <stdlib.h>

void password_generator(size_t password_length, char *password,
                        bool lower_include, bool upper_include,
                        bool num_include, bool symbol_include);

#endif
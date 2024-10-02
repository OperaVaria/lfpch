/*

Lightning-Fast Password Check v1.0.0
By OperaVaria, 2024

Placeholder for short description

This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public
License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later
version.

This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied
warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with this program. If not,
see <https://www.gnu.org/licenses/>

*/

#include <stdio.h>
#include <string.h>
#include <curl/curl.h>
#include <openssl/sha.h>
#include "auxfunc.h"
#include "types.h"

// Main function.
int main(int argc, char const *argv[]) {

    // Create Password struct instance.
    Password p1;

    // Get input.
    printf("Enter password: ");
    get_input(p1.data, PASSWORD_MAX_LENGTH, stdin);
    
    // Generate hash.
    size_t length = strlen(p1.data);
    SHA1(p1.data, length, p1.digest);
    
    // Print hash.
    for (int i=0; i<SHA_DIGEST_LENGTH; i++) {
	    printf("%02x", p1.digest[i]);
    }
    putchar('\n');

    // Get first 5 characters of the digest.
    memcpy(p1.first_five, p1.digest, 5); 
    
    // Print first 5 characters
    for (int j=0; j<=5; j++) {
	    printf("%02x", p1.first_five[j]);
    }
    putchar('\n');

    return 0;
}

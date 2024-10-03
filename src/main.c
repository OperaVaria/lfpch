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

// Header files.
#include <stdio.h>
#include <string.h>
#include "auxfunc.h"
#include "hashing.h"
#include "macros.h"
#include "requests.h"
#include "types.h"

// Main function.
int main(int argc, char const *argv[]) {

    // Create Password struct instance.
    Password p1;

    // Get input.
    printf("Enter password: ");
    get_input(p1.data, PASSWORD_MAX_LENGTH, stdin);

    // HASH.

    // Call hashing functions.
    generate_sha1(&p1);
    convert_digest(&p1);
    split_digest_str(&p1);   
   
    // REQUEST.    

    // Build request url.
    char url[64];
    sprintf(url, "https://api.pwnedpasswords.com/range/%s", p1.prefix);
    printf("%s\n", url);

    // Call cURL session function.
    curl_session(url);    

    return 0;
}

/*

Lightning-Fast Password Check v1.0.0
By OperaVaria, 2024

Placeholder for short description.

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
#include <stdlib.h>
#include <string.h>
#include "strop.h"
#include "hashing.h"
#include "macros.h"
#include "requests.h"
#include "types.h"

// Main function.
int main(int argc, char const *argv[]) {

    /* GET PASSWORD */

    // Create Password struct instance.
    Password p1;

    // Get password input.
    printf("Enter password: ");
    get_input(p1.data, PASSWORD_MAX_LENGTH, stdin);
    
    /* HASHING */

    // Call hashing functions.
    generate_sha1(p1.data, p1.digest);
    convert_digest(p1.digest, p1.digest_str);
    split_digest_str(p1.digest_str, p1.prefix, p1.suffix);

    /* REQUEST */

    // Build request url.
    char url[64];
    sprintf(url, "https://api.pwnedpasswords.com/range/%s", p1.prefix);   

    // Call cURL session function.
    Memory m1 = {0};
    curl_session(url, &m1); // TODO: Add error handling 

    //Search for suffix in response string.
    char *line_ptr = strstr(m1.string, p1.suffix);
        
    if (line_ptr != NULL) {
        // Get number of occurrences. TODO: put in function.
        char *start_ptr = strchr(line_ptr, ':');
        char *end_ptr = strchr(line_ptr, '\r');
        start_ptr++;
        end_ptr--;
        p1.pwn_num = copy_substring(start_ptr, end_ptr);
        printf("Password found %s times!\n", p1.pwn_num);
    } 
    else {
        printf("Password not found!\n");
    }

    free(m1.string); free(p1.pwn_num);

    return 0;
}

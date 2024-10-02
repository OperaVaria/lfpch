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

#include <ctype.h>
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
    get_input(p1.data, 64, stdin);

    // HASHING

    // Generate hash.
    size_t length = strlen(p1.data);
    SHA1(p1.data, length, p1.digest);
    
    // Create actual char string from hex array.
    for (int i = 0; i < SHA_DIGEST_LENGTH; i++) {
        sprintf(p1.digest_str + i*2, "%02x", p1.digest[i]);
    }
    p1.digest_str[SHA_DIGEST_LENGTH*2] = '\0';

    // Create prefix and suffix.
    for (int j = 0; j < SHA_DIGEST_LENGTH*2; j++) {
        
        p1.digest_str[j] = toupper(p1.digest_str[j]);

        if (j < 5) {
            p1.prefix[j] = p1.digest_str[j];
        }

        else if (j == 5) {
            p1.prefix[j] = '\0';
        }

        else {
            p1.suffix[j - 6] = p1.digest_str[j];
        }
    }
   
     // REQUEST.
    
    // Declare variables.
    CURL *curl;
    CURLcode res;
    char url[64];

    // Build url.
    sprintf(url, "https://api.pwnedpasswords.com/range/%s", p1.prefix);

    printf("%s\n", url);

    // Init "easy" API  session and error handling.
    curl = curl_easy_init();
    if (curl == NULL) {
        fprintf(stderr, "HTTP request failed\n");
        return -1;
    }
    
    // cURL setup.
    curl_easy_setopt(curl, CURLOPT_URL, url);
    
    // Perform request (with error handling).
    res = curl_easy_perform(curl);
    if (res != CURLE_OK) {
        fprintf(stderr, "Error: %s\n", curl_easy_strerror(res));
        return -1;
    }
    putchar('\n');

    // Close session.
    curl_easy_cleanup(curl);

    return 0;
}

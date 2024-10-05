/*

backend.c

Functions related to backend processes.

Part of the "Lightning-Fast Password Check" project by OperaVaria.

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

// A process of backend function calls.
char *backend_process(const char *password) {
    
    // Create Password struct instance.
    Password p1;

    // Copy password data to struct.
    strncpy(p1.data, password, PASSWORD_MAX_LENGTH);
    
    /* HASHING */

    // Call hashing functions.
    generate_sha1(p1.data, p1.digest);
    convert_digest(p1.digest, p1.digest_str);
    split_digest_str(p1.digest_str, p1.prefix, p1.suffix);
    
    printf("%s\n", p1.suffix);

    /* REQUEST */

    // Build request url.
    char url[64];
    sprintf(url, "https://api.pwnedpasswords.com/range/%s", p1.prefix);

    // Create Memory instance to store response chunks.
    Memory m1;
    m1.string = malloc(1);
    m1.size = 0;

    // Call cURL session function.
    curl_session(url, &m1);

    // Call response handling function to get pwn number.
    char* pwn_num = haveibeenpwned_res_hand(m1.string, p1.suffix);

    free(m1.string);

    return pwn_num;
}

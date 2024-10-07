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
#include "request.h"
#include "types.h"

/* Processes backend function calls. Takes a Password struct instance as argument.
Returns the number the password has been in a data breach, or NULL if not found. */ 
char *backend_process(Password *password_ptr) {   
        
    /* HASHING */

    // Call hashing functions.
    generate_sha1(password_ptr->pass_data, password_ptr->digest);
    convert_digest(password_ptr->digest, password_ptr->digest_str);
    split_digest_str(password_ptr->digest_str, password_ptr->prefix, password_ptr->suffix);

    /* REQUEST */

    // Build request url.
    char url[64];
    sprintf(url, "https://api.pwnedpasswords.com/range/%s", password_ptr->prefix);

    // Create Memory struct instance to store response chunks.
    Memory memory;
    memory.string = malloc(1);
    memory.size = 0;

    // Call cURL session function.
    curl_session(url, &memory);

    // Call response handling function to get pwn number.
    char *pwn_num = haveibeenpwned_res_hand(memory.string, password_ptr->suffix);

    // Free response string memory.
    free(memory.string);

    return pwn_num;
}

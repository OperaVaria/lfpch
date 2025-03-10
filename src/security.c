/*

security.c

Functions related to security measures.

Part of the "Lightning-Fast Password Check" project by OperaVaria.

*/

// Header files.
#include "security.h"
#include "types.h"

/* Zeroes the Password struct's character arrays,
that hold password related data, for added security. */
void clear_password_data(Password *password_ptr) {
    password_ptr->input_data = NULL;
    memset(password_ptr->gen_data, 0, sizeof(password_ptr->gen_data));
    memset(password_ptr->digest, 0, sizeof(password_ptr->digest));
    memset(password_ptr->digest_str, 0, sizeof(password_ptr->digest_str));
    memset(password_ptr->prefix, 0, sizeof(password_ptr->prefix));
    memset(password_ptr->suffix, 0, sizeof(password_ptr->suffix));
}

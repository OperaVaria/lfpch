/*

types.h

Header file containing custom types.

Part of the "Lightning-Fast Password Check" project by OperaVaria.

*/

// Guard.
#ifndef TYPES_H
#define TYPES_H

// Header files.
#include <gtk/gtk.h>
#include <openssl/sha.h>
#include "macros.h"

/* Memory location for a string.
Mainly used by the cURL callback function. */
typedef struct Memory {
    char *string;
    size_t size;
} Memory;

// Struct to store all password data needed for operation.
typedef struct Password {
    char const *pass_data;
    size_t pass_size;
    unsigned char digest[SHA_DIGEST_LENGTH];
    char digest_str[DIGEST_STRING_LENGTH];
    char prefix[PREFIX_LENGTH];
    char suffix[SUFFIX_LENGTH];
    long int pwn_num;
} Password;

/* Struct to store GTK widget pointers.
Used to pass multiple gpointers to GUI callback functions. */
typedef struct Widgets {
    // GtkWidget *button;
    // GtkTextBuffer* buffer;
    GtkWidget *entry;    
    GtkWidget *label;    
} Widgets;

#endif

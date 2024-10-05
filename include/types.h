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

// Struct to store all password data needed.
typedef struct Password {
    char data[PASSWORD_MAX_LENGTH];
    unsigned char digest[SHA_DIGEST_LENGTH];
    char digest_str[DIGEST_STRING_LENGTH];
    char prefix[PREFIX_LENGTH];
    char suffix[SUFFIX_LENGTH];
} Password;

/* Struct to store GTK widgets.
Used to pass multiple gpointers to the callback function. */
typedef struct Widgets {
    GtkWidget *entry;
    GtkWidget *button;
    GtkWidget *label;    
} Widgets;

#endif

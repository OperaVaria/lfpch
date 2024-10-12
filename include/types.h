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

// Struct to store all password data needed for the operation.
typedef struct Password {
    char const *input_data;
    char gen_data[PASSWORD_MAX_LENGTH + 1];
    unsigned char digest[SHA_DIGEST_LENGTH];
    char digest_str[DIGEST_STRING_LENGTH];
    char prefix[PREFIX_LENGTH];
    char suffix[SUFFIX_LENGTH];
    size_t length;
    int strength_score;
    long int pwn_num;
} Password;

/* Struct to store GTK widget pointers.
Used to pass multiple gpointers to GUI callback functions. */
typedef struct Widgets {
    GtkWidget *instruction_label;
    GtkWidget *password_entry;
    GtkWidget *submit_button;
    GtkWidget *strength_info_label;
    GtkWidget *strength_label;
    GtkWidget *strength_bar;
    GtkWidget *pwn_info_label;
    GtkWidget *pwn_label;
    GtkWidget *length_dropdown;
    GtkWidget *lower_check;
    GtkWidget *upper_check;
    GtkWidget *num_check;
    GtkWidget *symbol_check;
    GtkWidget *generate_button;
} Widgets;

#endif

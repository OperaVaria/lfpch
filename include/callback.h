/*

callback.h

Header file for callback.c.

Part of the "Lightning-Fast Password Check" project by OperaVaria.

*/

// Guard.
#ifndef CALLBACK_H
#define CALLBACK_H

// Header files.
#include <gtk/gtk.h>

// Function prototypes.
void check_callback(GtkWidget *button, gpointer password_entry);
void generate_callback(GtkWidget *button, gpointer data);
void on_window_destroy(GtkWidget *widget, gpointer data);

#endif

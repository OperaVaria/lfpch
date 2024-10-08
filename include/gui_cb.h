/*

gui_cb.h

Header file for gui_cb.c.

Part of the "Lightning-Fast Password Check" project by OperaVaria.

*/

// Guard.
#ifndef GUI_CB_H
#define GUI_CB_H

// Header files.
#include <gtk/gtk.h>

// Function prototypes.
void check_callback(GtkWidget *button, gpointer password_entry);
void generate_callback(GtkWidget *button, gpointer data);
void on_window_destroy(GtkWidget *widget, gpointer data);

#endif

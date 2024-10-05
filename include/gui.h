/*

gui.h

Header file for gui.h.

Part of the "Lightning-Fast Password Check" project by OperaVaria.

*/

// Guard.
#ifndef GUI_H
#define GUI_H

// Header files.
#include <gtk/gtk.h>

// Function prototypes.
void activate(GtkApplication *app, gpointer user_data);
void submit_callback(GtkWidget *button, gpointer password_entry);

#endif

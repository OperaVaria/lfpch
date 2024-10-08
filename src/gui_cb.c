/*

gui_cb.c

GUI callback functions.

Part of the "Lightning-Fast Password Check" project by OperaVaria.

*/

// Header files.
#include <gtk/gtk.h>
#include "backend.h"
#include "gui.h"
#include "gui_cb.h"
#include "types.h"

/* Callback function when a password is submitted to be checked
(submit button or enter press). */
void check_callback(GtkWidget *button, gpointer data) {

    // Declare variables.
    Widgets *widgets_ptr;
    char result_buffer[256];

    // Cast to the Widgets struct.
    widgets_ptr = (Widgets *)data;

    // Create Password struct instance, store password data and size.
    Password password;
    password.pass_data = gtk_editable_get_text(GTK_EDITABLE(widgets_ptr->entry));
    password.pass_size = strlen(password.pass_data);

    // Check if password too long.
    if (password.pass_size > PASSWORD_MAX_LENGTH) {

        // Too long: display warning, abort.
        gtk_label_set_text(GTK_LABEL(widgets_ptr->label), "Password too long!");

    } else {

        // Else: call backend process.
        password_check_process(&password);

        // Create label string based on the result.
        if (password.pwn_num != 0) {
            snprintf(result_buffer, sizeof(result_buffer), "This password has been hacked %'ld times\nbefore!", password.pwn_num);
        } else {
            snprintf(result_buffer, sizeof(result_buffer), "Password not found.");
        }

        // Update label.
        gtk_label_set_text(GTK_LABEL(widgets_ptr->label), result_buffer);
    }
}

// Callback function when "generate" button is clicked.
void generate_callback(GtkWidget *button, gpointer data) {

    // Declare variables.
    unsigned int selection_index;
    Password password;
    Widgets *widgets_ptr;

    // Cast to the Widgets struct.
    widgets_ptr = (Widgets *)data;

    // Get the index of the selected value.
    selection_index = gtk_drop_down_get_selected(GTK_DROP_DOWN(widgets_ptr->dropdown));

    // Add 4 to index to get value.
    password.pass_size = selection_index + 4;

    // Call password generator function.
    password_generator(password.pass_size, password.gen_pass);

    // Display newly generated password and notification.
    gtk_editable_set_text(GTK_EDITABLE(widgets_ptr->entry), password.gen_pass);
    gtk_label_set_text(GTK_LABEL(widgets_ptr->label), "Secure password generated!");
}

// Callback function on window destroy: free memory allocated for widgets.
void on_window_destroy(GtkWidget *widget, gpointer data) {
    Widgets *widgets_ptr = (Widgets *)data;
    g_free(widgets_ptr);
}

/*

callback.c

(GUI) callback functions.

Part of the "Lightning-Fast Password Check" project by OperaVaria.

*/

// Header files.
#include <gtk/gtk.h>
#include "backend.h"
#include "gui.h"
#include "callback.h"
#include "types.h"

/* Callback function when a password is submitted to be checked
(submit button or enter key press). */
void check_callback(GtkWidget *button, gpointer data) {

    // Declare variables.
    Widgets *widgets_ptr;
    char result_buffer[256];

    // (Re)cast to Widgets struct.
    widgets_ptr = (Widgets *)data;

    // Create Password struct instance, store password data and size.
    Password password;
    password.pass_data = gtk_editable_get_text(GTK_EDITABLE(widgets_ptr->password_entry));
    password.pass_size = strlen(password.pass_data);

    // Check if password too long.
    if (password.pass_size > PASSWORD_MAX_LENGTH) {

        // Too long: display warning, abort.
        gtk_label_set_text(GTK_LABEL(widgets_ptr->result_label), "Password too long!");

    } else {

        // Else: call backend process.
        password_check_process(&password);

        // Create label string based on the result.
        if (password.pwn_num != 0) {
            snprintf(result_buffer, sizeof(result_buffer),
                     "This password has been hacked %'ld times\nbefore!", password.pwn_num);
        } else {
            snprintf(result_buffer, sizeof(result_buffer), "Password not found.");
        }

        // Update label.
        gtk_label_set_text(GTK_LABEL(widgets_ptr->result_label), result_buffer);
    }
}

// Callback function when password generate button is clicked.
void generate_callback(GtkWidget *button, gpointer data) {

    // Declare variables.
    bool lower_include, upper_include, num_include, symbol_include;
    unsigned int selection_index;    
    Password password;
    Widgets *widgets_ptr;

    // (Re)cast to Widgets struct.
    widgets_ptr = (Widgets *)data;

    // Get the index of the selected value.
    selection_index = gtk_drop_down_get_selected(GTK_DROP_DOWN(widgets_ptr->length_dropdown));

    // Add 4 to index to get size value.
    password.pass_size = selection_index + 4;

    // Get the status of the checkboxes.
    lower_include = gtk_check_button_get_active (GTK_CHECK_BUTTON(widgets_ptr->lower_check));
    upper_include = gtk_check_button_get_active (GTK_CHECK_BUTTON(widgets_ptr->upper_check));
    num_include = gtk_check_button_get_active (GTK_CHECK_BUTTON(widgets_ptr->num_check));
    symbol_include = gtk_check_button_get_active (GTK_CHECK_BUTTON(widgets_ptr->symbol_check));

    // If all checks set to off: activate lower as a default.
    if (!lower_include && !upper_include && !num_include && !symbol_include) {
        lower_include = true;
        gtk_check_button_set_active(GTK_CHECK_BUTTON(widgets_ptr->lower_check), true);
    }

    // Call password generator function.
    password_generator(password.pass_size, password.gen_pass,
                       lower_include, upper_include, num_include, symbol_include);

    // Display newly generated password and notification.
    gtk_editable_set_text(GTK_EDITABLE(widgets_ptr->password_entry), password.gen_pass);
    gtk_label_set_text(GTK_LABEL(widgets_ptr->result_label), "Secure password generated!");
}

// Callback function on window destroy: free memory allocated for widgets.
void on_window_destroy(GtkWidget *widget, gpointer data) {
    Widgets *widgets_ptr = (Widgets *)data;
    g_free(widgets_ptr);
}

/*

gui.c

Functions related the user interface.

Part of the "Lightning-Fast Password Check" project by OperaVaria.

*/

// Header files.
#include <string.h>
#include <gtk/gtk.h>
#include "backend.h"
#include "macros.h"
#include "gui.h"
#include "types.h"

// Set up GUI structure.
void activate(GtkApplication *app, gpointer user_data) {

    // Declare widget variables.
    GtkWidget *window, *vbox, *instruction_label, *password_entry, *submit_button, *result_label;

    // Create window.
    window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), "Lightning-Fast Password Check");
    gtk_window_set_default_size (GTK_WINDOW (window), 400, 250);

    // Create vbox.
    vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_window_set_child(GTK_WINDOW(window), vbox);

    // Create an instruction label.
    instruction_label = gtk_label_new("Enter your password:");
    gtk_box_append(GTK_BOX(vbox), instruction_label);
    gtk_widget_set_margin_top(instruction_label, 20);
    gtk_widget_set_margin_start(instruction_label, 10);
    gtk_widget_set_margin_end(instruction_label, 10);

    // Create password entry field.
    password_entry = gtk_password_entry_new();    
    gtk_password_entry_set_show_peek_icon(GTK_PASSWORD_ENTRY(password_entry), true);
    gtk_box_append(GTK_BOX(vbox), password_entry);
    gtk_widget_set_margin_top(password_entry, 10);
    gtk_widget_set_margin_start(password_entry, 20);
    gtk_widget_set_margin_end(password_entry, 20);

    // Create "submit" button.
    submit_button = gtk_button_new_with_label("Check Password");
    gtk_box_append(GTK_BOX(vbox), submit_button);
    gtk_widget_set_margin_top(submit_button, 10);
    gtk_widget_set_margin_start(submit_button, 20);
    gtk_widget_set_margin_end(submit_button, 20);

    // Create info label.
    result_label = gtk_label_new("The result will be displayed here");
    gtk_label_set_justify(GTK_LABEL(result_label), GTK_JUSTIFY_CENTER);
    gtk_label_set_wrap(GTK_LABEL(result_label), true);
    gtk_box_append(GTK_BOX(vbox), result_label);
    gtk_widget_set_margin_top(result_label, 20);
    gtk_widget_set_margin_bottom(result_label, 20);
    gtk_widget_set_margin_start(result_label, 20);
    gtk_widget_set_margin_end(result_label, 20);

    // Allocate memory for Widgets struct.
    Widgets *widgets = g_new(Widgets, 1);
    widgets->entry = password_entry;
    widgets->label = result_label;

    // Connect callback functions.
    g_signal_connect (password_entry, "activate", G_CALLBACK (submit_callback), widgets);
    g_signal_connect(submit_button, "clicked", G_CALLBACK(submit_callback), widgets);
    g_signal_connect(window, "destroy", G_CALLBACK(on_window_destroy), widgets);

    gtk_window_present(GTK_WINDOW(window));
}

// Callback function on entry submit.
void submit_callback(GtkWidget *button, gpointer data) {

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
        backend_process(&password);

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

// Callback function on window destroy: free memory allocated for widgets.
void on_window_destroy(GtkWidget *widget, gpointer data) {
    Widgets *widgets_ptr = (Widgets *)data;
    g_free(widgets_ptr);
}

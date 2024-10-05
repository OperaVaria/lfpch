/*

gui.c

Functions related the user interface.

Part of the "Lightning-Fast Password Check" project by OperaVaria.

*/

// Header files.
#include "gui.h"
#include "backend.h"
#include "types.h"

// Set up GUI structure.
void activate(GtkApplication *app, gpointer user_data) {

    // Declare widget variables.
    GtkWidget *window;
    GtkWidget *grid;
    GtkWidget *password_entry;
    GtkWidget *submit_button;
    GtkWidget *result_label;

    // Create a new window, set title and resolution.
    window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), "Lightning-Fast Password Check");
    // gtk_window_set_default_size (GTK_WINDOW (window), 640, 480);

    // Create grid container, pack it in window.
    grid = gtk_grid_new();
    gtk_window_set_child(GTK_WINDOW(window), grid);

    // Create password entry field.
    password_entry = gtk_password_entry_new();
    // gtk_entry_set_max_length(GTK_PASSWORD_ENTRY(password_entry), 63);
    gtk_password_entry_set_show_peek_icon(GTK_PASSWORD_ENTRY(password_entry), true);    
    gtk_grid_attach(GTK_GRID(grid), password_entry, 0, 0, 1, 1);

    // Create "submit" button.
    submit_button = gtk_button_new_with_label("Submit");    
    gtk_grid_attach(GTK_GRID(grid), submit_button, 0, 1, 1, 1);

    // Info field.
    result_label = gtk_label_new("Result displayed here");
    gtk_grid_attach(GTK_GRID(grid), result_label, 0, 2, 1, 1);

    // Create a Widgets instance to hold widgets
    Widgets w1 = { password_entry, submit_button, result_label };

    // Connect callback function.
    // g_signal_connect (password_entry, "activate", G_CALLBACK (submit_callback), &w1);
    g_signal_connect(submit_button, "clicked", G_CALLBACK(submit_callback), &w1);    
    gtk_window_present(GTK_WINDOW(window));
}

// Callback function to execute when the "submit" button is pressed.
void submit_callback(GtkWidget *button, gpointer data) {

    // Cast gpointer to the struct.
    Widgets *widgets = (Widgets *)data;  

    // Get the password entered in the password entry field.
    const char *password = gtk_editable_get_text(GTK_EDITABLE (widgets->entry));    

    // Launch backend process:
    const char *number = backend_process(password);

    // Update the label.
    char buffer[256];
    snprintf(buffer, sizeof(buffer), "Password: count %s", number);
    gtk_label_set_text(GTK_LABEL(widgets->label), buffer);
}

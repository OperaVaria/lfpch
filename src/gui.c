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
    gtk_box_append(GTK_BOX(vbox), password_entry);
    gtk_password_entry_set_show_peek_icon(GTK_PASSWORD_ENTRY(password_entry), true);    
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
    result_label = gtk_label_new("Result will be displayed here");
    gtk_box_append(GTK_BOX(vbox), result_label);
    gtk_widget_set_margin_top(result_label, 20);
    gtk_widget_set_margin_bottom(result_label, 20);
    gtk_widget_set_margin_start(result_label, 20);
    gtk_widget_set_margin_end(result_label, 20);

    // Allocate memory for Widgets struct.
    Widgets *w1 = g_new(Widgets, 1);
    w1->entry = password_entry;
    w1->button = submit_button;
    w1->label = result_label;

    // Connect callback functions.
    g_signal_connect (password_entry, "activate", G_CALLBACK (submit_callback), w1);
    g_signal_connect(submit_button, "clicked", G_CALLBACK(submit_callback), w1);
    g_signal_connect(window, "destroy", G_CALLBACK(on_window_destroy), w1);
        
    gtk_window_present(GTK_WINDOW(window));
}

// Callback function on entry submit.
void submit_callback(GtkWidget *button, gpointer data) {

    // Declare variables.
    Widgets *widgets_ptr;
    const char *password;
    char *result_num, result_buffer[256];

    // Cast to the widget struct.
    widgets_ptr = (Widgets *)data;

    // Get input, and process backend session.
    password = get_password_from_entry(widgets_ptr);
    result_num = backend_process(password);

    // Create label string based on the result.
    if (result_num != NULL) {
        snprintf(result_buffer, sizeof(result_buffer), "Password pwned %s times!", result_num);
    } else {
        snprintf(result_buffer, sizeof(result_buffer), "Password not found.");
    }

    // Free result_num (manually allocated in callback process).
    free(result_num);

    // Update label.
    update_result_label(widgets_ptr, result_buffer);
}

// Callback function on window destroy: free memory allocated for widgets.
void on_window_destroy(GtkWidget *widget, gpointer data) {
    Widgets *widgets_ptr = (Widgets *)data;
    g_free(widgets_ptr);
}

// Helper functions.
const char *get_password_from_entry(Widgets *widgets_ptr) {
    return gtk_editable_get_text(GTK_EDITABLE(widgets_ptr->entry));
}

void update_result_label(Widgets *widgets, const char *text) {
    gtk_label_set_text(GTK_LABEL(widgets->label), text);
}

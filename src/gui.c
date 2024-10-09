/*

gui.c

Functions related the user interface structure.

Part of the "Lightning-Fast Password Check" project by OperaVaria.

*/

// Header files.
#include <string.h>
#include <gtk/gtk.h>
#include "gui.h"
#include "callback.h"
#include "macros.h"
#include "types.h"

// Set up GUI structure.
void activate(GtkApplication *app, gpointer user_data) {

    // Declare GTK variables.
    GtkWidget *window, *vbox, *hbox,
              *instruction_label, *generator_label, *length_label, *result_label,
              *password_entry,
              *length_dropdown,
              *generate_button, *submit_button,
              *lower_check, *upper_check, *num_check, *symbol_check;
    GtkStringList *string_list;

    // Create window.
    window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), "Lightning-Fast Password Check");
    // gtk_window_set_default_size (GTK_WINDOW (window), 640, 410);
    gtk_window_set_resizable(GTK_WINDOW (window), FALSE);

    // Create horizontal box as general container.
    vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_window_set_child(GTK_WINDOW(window), vbox);

    // Create an instruction label.
    instruction_label = gtk_label_new("Enter or generate password:");
    gtk_box_append(GTK_BOX(vbox), instruction_label);
    gtk_widget_set_margin_top(instruction_label, 25);

    // Create password entry field.
    password_entry = gtk_password_entry_new();
    gtk_password_entry_set_show_peek_icon(GTK_PASSWORD_ENTRY(password_entry), true);
    gtk_box_append(GTK_BOX(vbox), password_entry);
    gtk_widget_set_margin_top(password_entry, 10);
    gtk_widget_set_margin_start(password_entry, 50);
    gtk_widget_set_margin_end(password_entry, 50);

    // Create password "submit" button.
    submit_button = gtk_button_new_with_label("Check Password");
    gtk_box_append(GTK_BOX(vbox), submit_button);
    gtk_widget_set_margin_top(submit_button, 10);
    gtk_widget_set_margin_start(submit_button, 50);
    gtk_widget_set_margin_end(submit_button, 50);

    // Create info label.
    result_label = gtk_label_new("The result will be displayed here");
    gtk_label_set_justify(GTK_LABEL(result_label), GTK_JUSTIFY_CENTER);
    gtk_label_set_wrap(GTK_LABEL(result_label), true);
    gtk_box_append(GTK_BOX(vbox), result_label);
    gtk_widget_set_margin_top(result_label, 20);
    gtk_widget_set_margin_bottom(result_label, 20);
    gtk_widget_set_margin_start(result_label, 20);
    gtk_widget_set_margin_end(result_label, 20);
    gtk_widget_set_size_request(result_label, -1, 50);

    // Create generator label
    generator_label = gtk_label_new("Password generator settings:");
    gtk_box_append(GTK_BOX(vbox), generator_label);
    gtk_widget_set_margin_top(generator_label, 10);
    gtk_widget_set_margin_start(generator_label, 10);
    gtk_widget_set_margin_end(generator_label, 10);

    // Create vertical box for the generator settings widgets.
    hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
    gtk_box_append(GTK_BOX(vbox), hbox);
    gtk_widget_set_margin_top(hbox, 10);
    gtk_widget_set_margin_start(hbox, 25);
    gtk_widget_set_margin_end(hbox, 25);

    // Create label for dropdown menu.
    length_label = gtk_label_new("Password length:");
    gtk_box_append(GTK_BOX(hbox), length_label);

    /* Create string list to store password length options
    (numbers 4 to PASSWORD_MAX_LENGTH).
    Conversion to stings unfortunate, but needed. */
    string_list = gtk_string_list_new(NULL);
    for (int i = 4; i <= PASSWORD_MAX_LENGTH; i++) {
        char conversion_buffer[3];
        snprintf(conversion_buffer, sizeof(conversion_buffer), "%d", i);
        gtk_string_list_append(string_list, conversion_buffer);
    }

    // Create dropdown menu for password length, default : 16 char.
    length_dropdown = gtk_drop_down_new(G_LIST_MODEL(string_list), NULL);
    gtk_drop_down_set_selected(GTK_DROP_DOWN(length_dropdown), 16 - 4);
    gtk_widget_set_size_request(length_dropdown, 60, -1);
    gtk_box_append(GTK_BOX(hbox), length_dropdown);

    // Create check buttons (4 char types):

    lower_check = gtk_check_button_new_with_label("Lowercase");
    gtk_check_button_set_active(GTK_CHECK_BUTTON(lower_check), true);
    gtk_box_append(GTK_BOX(hbox), lower_check);

    upper_check = gtk_check_button_new_with_label("Uppercase");
    gtk_check_button_set_active(GTK_CHECK_BUTTON(upper_check), true);
    gtk_box_append(GTK_BOX(hbox), upper_check);

    num_check = gtk_check_button_new_with_label("Numbers"),
    gtk_check_button_set_active(GTK_CHECK_BUTTON(num_check), true);
    gtk_box_append(GTK_BOX(hbox), num_check);

    symbol_check = gtk_check_button_new_with_label("Symbols");
    gtk_check_button_set_active(GTK_CHECK_BUTTON(symbol_check), true);
    gtk_box_append(GTK_BOX(hbox), symbol_check);

    // Create "generate" button.
    generate_button = gtk_button_new_with_label("Generate Secure Password");
    gtk_box_append(GTK_BOX(vbox), generate_button);
    gtk_widget_set_margin_top(generate_button, 10);
    gtk_widget_set_margin_bottom(generate_button, 25);
    gtk_widget_set_margin_start(generate_button, 50);
    gtk_widget_set_margin_end(generate_button, 50);

    // Allocate memory for Widgets struct and initialize.
    Widgets *widgets = g_new(Widgets, 1);
    widgets->password_entry = password_entry;
    widgets->lower_check = lower_check;
    widgets->upper_check = upper_check;
    widgets->num_check = num_check;
    widgets->symbol_check = symbol_check;
    widgets->length_dropdown = length_dropdown;
    widgets->result_label = result_label;

    // Connect callback functions.
    g_signal_connect(password_entry, "activate", G_CALLBACK(check_callback), widgets);
    g_signal_connect(generate_button, "clicked", G_CALLBACK(generate_callback), widgets);
    g_signal_connect(submit_button, "clicked", G_CALLBACK(check_callback), widgets);
    g_signal_connect(window, "destroy", G_CALLBACK(on_window_destroy), widgets);


    gtk_window_present(GTK_WINDOW(window));
}

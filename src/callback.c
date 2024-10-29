/*

callback.c

(GUI) callback functions.

Part of the "Lightning-Fast Password Check" project by OperaVaria.

*/

// Header files.
#include <gtk/gtk.h>
#include "checker.h"
#include "generator.h"
#include "callback.h"
#include "types.h"
#include "security.h"

// Static function prototypes.
static void reset_result_widgets(Widgets *widgets_ptr, const char *display_text);
static void display_results(Widgets *widgets_ptr, Password *password_ptr);
static const char *get_strength_color(int strength);
static const char *get_strength_description(int strength);

/* Callback function when a password is submitted to be checked
(submit button or enter key press). */
void check_callback(GtkWidget *widget, gpointer data) {

    // Declare variables.
    Password password;
    Widgets *widgets_ptr;

    // (Re)cast to Widgets struct.
    widgets_ptr = (Widgets *)data;

    // Store password data and length in Password struct.
    password.input_data = gtk_editable_get_text(GTK_EDITABLE(widgets_ptr->password_entry));
    password.length = strlen(password.input_data);

    /* Check if no password entered or password is too long.
    If so: display warning to labels, reset strength bar, abort.
    Else: proceed normally. */
    if (password.input_data[0] == '\0') {
        reset_result_widgets(widgets_ptr, "No password entered!");
    } else if (password.length > PASSWORD_MAX_LENGTH) {
        reset_result_widgets(widgets_ptr, "Password too long!");
    } else {

        // Call backend processes (strength and pwn check).
        password.strength_score = password_strength_check(password.input_data, password.length);
        password.pwn_num = pwn_check_process(&password);

        // Display results with helper function.
        display_results(widgets_ptr, &password);

    }

    // Zero out password related data as a security measure.
    clear_password_data(&password);
}

// Callback function when password generate button is clicked.
void generate_callback(GtkWidget *button, gpointer data) {

    // Declare variables.
    Password password;
    Widgets *widgets_ptr;
    unsigned int selection_index;
    bool lower_include, upper_include, num_include, symbol_include;

    // (Re)cast to Widgets struct.
    widgets_ptr = (Widgets *)data;

    // Get the index of the selected value.
    selection_index = gtk_drop_down_get_selected(GTK_DROP_DOWN(widgets_ptr->length_dropdown));

    // Add password min length to index to get size value.
    password.length = selection_index + PASSWORD_MIN_LENGTH;

    // Get the status of the checkboxes.
    lower_include = gtk_check_button_get_active(GTK_CHECK_BUTTON(widgets_ptr->lower_check));
    upper_include = gtk_check_button_get_active(GTK_CHECK_BUTTON(widgets_ptr->upper_check));
    num_include = gtk_check_button_get_active(GTK_CHECK_BUTTON(widgets_ptr->num_check));
    symbol_include = gtk_check_button_get_active(GTK_CHECK_BUTTON(widgets_ptr->symbol_check));

    // If all checkboxes set to off: activate lower case as a default.
    if (!lower_include && !upper_include && !num_include && !symbol_include) {
        lower_include = true;
        gtk_check_button_set_active(GTK_CHECK_BUTTON(widgets_ptr->lower_check), true);
    }

    // Call password generator function.
    password_generator(password.gen_data, password.length,
                       lower_include, upper_include, num_include, symbol_include);

    // Display newly generated password.
    gtk_editable_set_text(GTK_EDITABLE(widgets_ptr->password_entry), password.gen_data);

    // Reset result widgets to default.
    reset_result_widgets(widgets_ptr, "n/a");

    // Zero out password related data as a security measure.
    clear_password_data(&password);
}

// Callback function on window destroy: free memory allocated for widgets.
void on_window_destroy(GtkWidget *widget, gpointer data) {
    Widgets *widgets_ptr = (Widgets *)data;
    g_free(widgets_ptr);
}

/* HELPER FUNCTIONS: */

/* Function to reset the result display widgets (pwn_label, strength_label,
strength_bar) to a default. Arguments: Widgets pointer, text to display. */
static void reset_result_widgets(Widgets *widgets_ptr, const char *display_text) {
    gtk_label_set_text(GTK_LABEL(widgets_ptr->pwn_label), display_text);
    gtk_label_set_text(GTK_LABEL(widgets_ptr->strength_label),display_text);
    gtk_progress_bar_set_fraction(GTK_PROGRESS_BAR(widgets_ptr->strength_bar), 0.0);
}

/* Function to display the results of the check process on the proper widgets.
Takes a pointer to a Widgets and a Password struct instance as arguments. */
static void display_results(Widgets *widgets_ptr, Password *password_ptr) {

    //Declare variables.
    char strength_msg_buff[128], pwn_msg_buff[128];

    // Update strength bar.
    gtk_progress_bar_set_fraction(GTK_PROGRESS_BAR(widgets_ptr->strength_bar),
                                  password_ptr->strength_score / 100.0);
    gtk_widget_set_name(widgets_ptr->strength_bar,
                        get_strength_color(password_ptr->strength_score));

    // Update strength label.
    snprintf(strength_msg_buff, sizeof(strength_msg_buff),
             get_strength_description(password_ptr->strength_score));
    gtk_label_set_text(GTK_LABEL(widgets_ptr->strength_label), strength_msg_buff);


    /* Create pwn result message based on result. The "'" format specifier
    (thousand separated number) does not work on Windows, therefore it is
    not implemented in the pwn result message. */
    if (password_ptr->pwn_num != 0) {
        #ifdef _WIN32
            snprintf(pwn_msg_buff, sizeof(pwn_msg_buff),
                        "Warning! This password has been breached at least %ld times!",
                        password_ptr->pwn_num);
        #else
            snprintf(pwn_msg_buff, sizeof(pwn_msg_buff),
                        "Warning! This password has been breached at least %'ld times!",
                        password_ptr->pwn_num);
        #endif
    } else {
        snprintf(pwn_msg_buff, sizeof(pwn_msg_buff), "Password is not known to be hacked!");
    }

    // Update pwn label.
    gtk_label_set_text(GTK_LABEL(widgets_ptr->pwn_label), pwn_msg_buff);
}

// Function to get color based on strength score.
static const char *get_strength_color(int strength) {
    if (strength < 20) return "red";
    if (strength < 40) return "orange";
    if (strength < 60) return "yellow";
    if (strength < 80) return "lightgreen";
    return "green";
}

// Function to get description based on strength score.
static const char *get_strength_description(int strength) {
    if (strength < 20) return "Very Weak";
    if (strength < 40) return "Weak";
    if (strength < 60) return "Moderate";
    if (strength < 80) return "Strong";
    return "Very Strong";
}

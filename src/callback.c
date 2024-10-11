/*

callback.c

(GUI) callback functions.

Part of the "Lightning-Fast Password Check" project by OperaVaria.

*/

// Header files.
#include <gtk/gtk.h>
#include "checker.h"
#include "generator.h"
#include "gui.h"
#include "callback.h"
#include "types.h"

// Static function prototypes.
static const char* get_strength_color(int strength);
static const char* get_strength_description(int strength);
static void reset_strength_bar(Widgets *widgets_ptr);

/* Callback function when a password is submitted to be checked
(submit button or enter key press). */
void check_callback(GtkWidget *button, gpointer data) {

    // Declare variables.
    Widgets *widgets_ptr;
    char strength_msg_buff[128], pwn_msg_buff[128];    

    // (Re)cast to Widgets struct.
    widgets_ptr = (Widgets *)data;

    // Create Password struct instance, store password data and length.
    Password password;
    password.input_data = gtk_editable_get_text(GTK_EDITABLE(widgets_ptr->password_entry));
    password.length = strlen(password.input_data);

    /* Check if no password entered or password is too long. Display warning to result label,
    reset strength label and bar, abort. */
    if (password.input_data[0] == '\0') {
        gtk_label_set_text(GTK_LABEL(widgets_ptr->result_label), "No password entered!");
        reset_strength_bar(widgets_ptr);
    } else if (password.length > PASSWORD_MAX_LENGTH) {
        gtk_label_set_text(GTK_LABEL(widgets_ptr->result_label), "Password too long!");
        reset_strength_bar(widgets_ptr);
    
    // Else: proceed.
    } else {

        // Call backend processes.
        password.strength_score = password_strength_check(password.input_data, password.length);
        password.pwn_num = pwn_check_process(&password);

        /* DISPLAY RESULTS */

        // Update strength bar.
        gtk_progress_bar_set_fraction(GTK_PROGRESS_BAR(widgets_ptr->strength_bar),
                                      password.strength_score / 100.0);
        gtk_widget_set_name(widgets_ptr->strength_bar,
                            get_strength_color(password.strength_score));

        // Update strength label.
        snprintf(strength_msg_buff, sizeof(strength_msg_buff), "Password Strength:\n<b>%s</b>",
                                         get_strength_description(password.strength_score));
        gtk_label_set_markup(GTK_LABEL(widgets_ptr->strength_label), strength_msg_buff);


        // Create pwn result message based on result.
        if (password.pwn_num != 0) {
            snprintf(pwn_msg_buff, sizeof(pwn_msg_buff),
                     "Warning! This password was breached atleast %ld times!", password.pwn_num);
        } else {
            snprintf(pwn_msg_buff, sizeof(pwn_msg_buff), "Password not known to be hacked!");
        }

        // Update pwn label.
        gtk_label_set_text(GTK_LABEL(widgets_ptr->result_label), pwn_msg_buff);
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

    // Add password min length to index to get size value.
    password.length = selection_index + PASSWORD_MIN_LENGTH;

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
    password_generator(password.length, password.gen_data,
                       lower_include, upper_include, num_include, symbol_include);
    
    // Reset strength bar.
    reset_strength_bar(widgets_ptr);

    // Display newly generated password and notification.
    gtk_editable_set_text(GTK_EDITABLE(widgets_ptr->password_entry), password.gen_data);
    gtk_label_set_text(GTK_LABEL(widgets_ptr->result_label), "Secure password generated!");
}

// Callback function on window destroy: free memory allocated for widgets.
void on_window_destroy(GtkWidget *widget, gpointer data) {
    Widgets *widgets_ptr = (Widgets *)data;
    g_free(widgets_ptr);
}

// HELPER FUNCTIONS:

// Function to get color based on strength score.
static const char* get_strength_color(int strength) {
    if (strength < 20) return "red";
    if (strength < 40) return "orange";
    if (strength < 60) return "yellow";
    if (strength < 80) return "lightgreen";
    return "green";
}

// Function to get description based on strength score.
static const char* get_strength_description(int strength) {
    if (strength < 20) return "Very Weak";
    if (strength < 40) return "Weak";
    if (strength < 60) return "Moderate";
    if (strength < 80) return "Strong";
    return "Very Strong";
}

// Resets strength bar and label.
static void reset_strength_bar(Widgets *widgets_ptr) {
    gtk_label_set_markup(GTK_LABEL(widgets_ptr->strength_label), "Password Strength:\n<b>n/a</b>");
    gtk_progress_bar_set_fraction(GTK_PROGRESS_BAR(widgets_ptr->strength_bar), 0.0);
}

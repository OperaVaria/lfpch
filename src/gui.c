/*

gui.c

Functions related to the user interface structure.

Part of the "Lightning-Fast Password Check" project by OperaVaria.

*/

// Header files.
// #include <string.h>
#include <gtk/gtk.h>
#include "gui.h"
#include "callback.h"
#include "macros.h"
#include "types.h"

// Static function prototypes.
static GtkWidget* create_window(GtkApplication *app);
static GtkWidget* create_main_container(void);
static void create_password_input_section(GtkWidget *vbox, Widgets *widgets);
static void create_strength_display_section(GtkWidget *vbox, Widgets *widgets);
static void create_pwn_display_section(GtkWidget *vbox, Widgets *widgets);
static void create_password_generator_section(GtkWidget *vbox, Widgets *widgets);
static void connect_signals(GtkWidget *window, Widgets *widgets);
static void add_css_provider(GtkWidget *window);

// Set up GUI structure.
void activate(GtkApplication *app, gpointer data) {

    // Declare variables.
    GtkWidget *window, *vbox;
    Widgets *widgets;

    // Create main window and container.
    window = create_window(app);
    vbox = create_main_container();
    gtk_window_set_child(GTK_WINDOW(window), vbox);

    // Allocate memory for Widgets struct.
    widgets = g_new(Widgets, 1);

    // Create GUI sections.
    create_password_input_section(vbox, widgets);
    create_strength_display_section(vbox, widgets);
    create_pwn_display_section(vbox, widgets);
    create_password_generator_section(vbox, widgets);

    // Connect callback functions.
    connect_signals(window, widgets);

    // Add CSS styling.
    add_css_provider(window);

    // Raise window to user.
    gtk_window_present(GTK_WINDOW(window));
}

/* Functions to create main elements. */

static GtkWidget* create_window(GtkApplication *app) {
    GtkWidget *window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), "Lightning-Fast Password Check");
    gtk_window_set_resizable(GTK_WINDOW(window), FALSE);
    return window;
}

static GtkWidget* create_main_container(void) {
    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    return vbox;
}

/* Functions to create widget sections. */

static void create_password_input_section(GtkWidget *vbox, Widgets *widgets) {

    // Declare variables.
    GtkWidget *instruction_label, *password_entry, *submit_button;

    // Create top instruction label.
    instruction_label = gtk_label_new("Enter or generate password:");
    gtk_box_append(GTK_BOX(vbox), instruction_label);
    gtk_widget_set_margin_top(instruction_label, 25);

    // Create password entry field.
    password_entry = gtk_password_entry_new();
    gtk_box_append(GTK_BOX(vbox), password_entry);
    gtk_password_entry_set_show_peek_icon(GTK_PASSWORD_ENTRY(password_entry), true);
    gtk_widget_set_margin_start(password_entry, 50);
    gtk_widget_set_margin_end(password_entry, 50);

    // Create password submit button.
    submit_button = gtk_button_new_with_label("Check Password");
    gtk_box_append(GTK_BOX(vbox), submit_button);
    gtk_widget_set_margin_start(submit_button, 50);
    gtk_widget_set_margin_end(submit_button, 50);

    // Add widget pointers to struct.
    widgets->instruction_label = instruction_label;
    widgets->password_entry = password_entry;
    widgets->submit_button = submit_button;
}

static void create_strength_display_section(GtkWidget *vbox, Widgets *widgets) {

    // Declare variables.
    GtkWidget *strength_info_label, *strength_label, *strength_bar;

    // Create info label.
    strength_info_label = gtk_label_new("Password strength:");
    gtk_box_append(GTK_BOX(vbox), strength_info_label);
    gtk_widget_set_margin_top(strength_info_label, 20);

    // Create label to display password strength message.
    strength_label = gtk_label_new("n/a");
    gtk_box_append(GTK_BOX(vbox), strength_label);
    gtk_label_set_justify(GTK_LABEL(strength_label), GTK_JUSTIFY_CENTER);
    gtk_widget_add_css_class (strength_label, "bold-font");

    // Create strength "progress" bar.
    strength_bar = gtk_progress_bar_new();
    gtk_box_append(GTK_BOX(vbox), strength_bar);
    gtk_progress_bar_set_show_text(GTK_PROGRESS_BAR(strength_bar), FALSE);
    gtk_widget_set_margin_start(strength_bar, 50);
    gtk_widget_set_margin_end(strength_bar, 50);

    // Add widget pointers to struct.
    widgets->strength_info_label = strength_info_label;
    widgets->strength_label = strength_label;
    widgets->strength_bar = strength_bar;
}

static void create_pwn_display_section(GtkWidget *vbox, Widgets *widgets) {

    // Declare variables.
    GtkWidget *pwn_info_label, *pwn_label;

    // Create info label.
    pwn_info_label = gtk_label_new("Breach database status:");
    gtk_box_append(GTK_BOX(vbox), pwn_info_label);
    gtk_widget_set_margin_top(pwn_info_label, 10);

    // Create data breach check result label.
    pwn_label = gtk_label_new("n/a");
    gtk_box_append(GTK_BOX(vbox), pwn_label);
    gtk_label_set_justify(GTK_LABEL(pwn_label), GTK_JUSTIFY_CENTER);
    gtk_widget_add_css_class (pwn_label, "bold-font");
    gtk_widget_set_margin_start(pwn_label, 20);
    gtk_widget_set_margin_end(pwn_label, 20);

    // Add widget pointers to struct.
    widgets->pwn_info_label = pwn_info_label;
    widgets->pwn_label = pwn_label;
}

static void create_password_generator_section(GtkWidget *vbox, Widgets *widgets) {

    // Declare variables.
    GtkWidget *generator_label, *hbox, *length_label, *length_dropdown,
              *lower_check, *upper_check, *num_check, *symbol_check, *generate_button;
    GtkStringList *string_list;

    // Create generator label.
    generator_label = gtk_label_new("Password generator settings:");
    gtk_box_append(GTK_BOX(vbox), generator_label);
    gtk_widget_set_margin_top(generator_label, 20);
    gtk_widget_set_margin_start(generator_label, 10);
    gtk_widget_set_margin_end(generator_label, 10);

    // Create horizontal box for generator setting widgets.
    hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
    gtk_box_append(GTK_BOX(vbox), hbox);
    gtk_widget_set_margin_start(hbox, 25);
    gtk_widget_set_margin_end(hbox, 25);

    // Create label for the password length dropdown menu.
    length_label = gtk_label_new("Password length:");
    gtk_box_append(GTK_BOX(hbox), length_label);

    /* Create string list to store password length options
    (PASSWORD_MIN_LENGTH to PASSWORD_MAX_LENGTH).
    Conversion to stings unfortunate, but needed. */
    string_list = gtk_string_list_new(NULL);
    for (int i = PASSWORD_MIN_LENGTH; i <= PASSWORD_MAX_LENGTH; i++) {
        char conversion_buffer[3];
        snprintf(conversion_buffer, sizeof(conversion_buffer), "%d", i);
        gtk_string_list_append(string_list, conversion_buffer);
    }

    /* Create dropdown menu to select password length.
    Default value:  16 chars. */
    length_dropdown = gtk_drop_down_new(G_LIST_MODEL(string_list), NULL);
    gtk_box_append(GTK_BOX(hbox), length_dropdown);
    gtk_drop_down_set_selected(GTK_DROP_DOWN(length_dropdown), 16 - PASSWORD_MIN_LENGTH);
    gtk_widget_set_size_request(length_dropdown, 60, -1);

    // Create character type check buttons:

    lower_check = gtk_check_button_new_with_label("Lowercase");
    gtk_check_button_set_active(GTK_CHECK_BUTTON(lower_check), true);
    gtk_box_append(GTK_BOX(hbox), lower_check);

    upper_check = gtk_check_button_new_with_label("Uppercase");
    gtk_check_button_set_active(GTK_CHECK_BUTTON(upper_check), true);
    gtk_box_append(GTK_BOX(hbox), upper_check);

    num_check = gtk_check_button_new_with_label("Numbers");
    gtk_check_button_set_active(GTK_CHECK_BUTTON(num_check), true);
    gtk_box_append(GTK_BOX(hbox), num_check);

    symbol_check = gtk_check_button_new_with_label("Symbols");
    gtk_check_button_set_active(GTK_CHECK_BUTTON(symbol_check), true);
    gtk_box_append(GTK_BOX(hbox), symbol_check);

    // Create generate button.
    generate_button = gtk_button_new_with_label("Generate Secure Password");
    gtk_box_append(GTK_BOX(vbox), generate_button);
    gtk_widget_set_margin_bottom(generate_button, 25);
    gtk_widget_set_margin_start(generate_button, 50);
    gtk_widget_set_margin_end(generate_button, 50);

    // Add widget pointers to struct.
    widgets->lower_check = lower_check;
    widgets->upper_check = upper_check;
    widgets->num_check = num_check;
    widgets->symbol_check = symbol_check;
    widgets->length_dropdown = length_dropdown;
    widgets->generate_button = generate_button;
}

/* Connect callback functions, pass Widgets struct to be able to interact with
multiple widgets in one callback function */
static void connect_signals(GtkWidget *window, Widgets *widgets) {
    g_signal_connect(widgets->password_entry, "activate", G_CALLBACK(check_callback), widgets);
    g_signal_connect(widgets->generate_button, "clicked", G_CALLBACK(generate_callback), widgets);
    g_signal_connect(widgets->submit_button, "clicked", G_CALLBACK(check_callback), widgets);
    g_signal_connect(window, "destroy", G_CALLBACK(on_window_destroy), widgets);
}

// Connect a CSS file to display.
static void add_css_provider(GtkWidget *window) {
    GtkCssProvider *provider = gtk_css_provider_new ();
    gtk_css_provider_load_from_file (provider, g_file_new_for_path ("./styles/styles.css"));
    gtk_style_context_add_provider_for_display (gtk_widget_get_display (window),
                                                GTK_STYLE_PROVIDER (provider),
                                                GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
}

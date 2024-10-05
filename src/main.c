/*

Lightning-Fast Password Check v1.0.0
By OperaVaria, 2024

Placeholder for short description.

This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public
License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later
version.

This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied
warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with this program. If not,
see <https://www.gnu.org/licenses/>

*/

// Header files.
#include <gtk/gtk.h>
#include "gui.h"

// Main function.
int main(int argc, char **argv) {

    // Declare variables.
    GtkApplication *app;
    int status;

    // Setup a GTK app instance.
    app = gtk_application_new("org.gtk.lfpch", G_APPLICATION_DEFAULT_FLAGS);
    g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
    status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);

    return status;
}

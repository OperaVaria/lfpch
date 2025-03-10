/*

Lightning-Fast Password Check v0.0.2
2025/03/11
By OperaVaria

LFPCh is a small, cross-platform GUI application to check if your password is safe to use.
The program conducts a two-step security check: In step one, the password's quality is evaluated
based on it's length and character variety. In step two, the app checks whether
the password was part of an earlier data breach through the haveibeenpwned.com API.
The application also includes a random password generator,based on a "true" random seed
provided by the x86 processor's DRNG unit.

License:

This program is free software: you can redistribute it and/or modify it under the terms
of the GNU General Public License as published by the Free Software Foundation,
either version 3 of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with this program.
If not, see <https://www.gnu.org/licenses/>

*/

// Header files.
#include <gtk/gtk.h>
#include "gui.h"

// Main function.
int main(int argc, char **argv) {

    // Declare variables.
    GtkApplication *app;
    int status;

    // Setup a GTK app instance with GLib version guard included.
    #if GLIB_CHECK_VERSION(2, 74, 0)
        app = gtk_application_new("org.gtk.lfpch", G_APPLICATION_DEFAULT_FLAGS);
    #else
        app = gtk_application_new("org.gtk.lfpch", G_APPLICATION_FLAGS_NONE);
    #endif    
    g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
    status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);

    return status;
}

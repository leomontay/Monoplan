#include <gtk/gtk.h>
#include "gui/gui.h"

int main(int argc, char *argv[])
{
    gtk_init(&argc, &argv);

    gui_init();

    gtk_main();
    return 0;
}
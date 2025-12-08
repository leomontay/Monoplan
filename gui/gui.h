#ifndef GUI_H
#define GUI_H

#include <gtk/gtk.h>
#include "../cellules/cellules.h"

typedef struct bind {
    int ligne;
    int colonne;
    GtkWidget *case_widget;
    s_cell *cell;
} s_bind;

void gui_init();
s_bind *bindLookupByCell(s_cell *cell);
s_bind *bindLookupByPos(int col, int lig);

#endif
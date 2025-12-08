#include "gui.h"
#include <stdio.h>

#define NB_LIGNES 10
#define NB_COLONNES 8

extern s_cell *tableau_cellules[];
extern int nb_cellules;

s_bind *bind_table[NB_LIGNES][NB_COLONNES];

GtkBuilder *builder;
GtkWidget *fenetre;
GtkWidget *grille;

s_cell *ajouter_cellule(int l, int c);

void bind_create(int l, int c, GtkWidget *widget, s_cell *cell)
{
    s_bind *b = malloc(sizeof(s_bind));
    b->ligne = l;
    b->colonne = c;
    b->case_widget = widget;
    b->cell = cell;
    bind_table[l][c] = b;
}

s_bind *bindLookupByCell(s_cell *cell)
{
    for (int i = 0; i < NB_LIGNES; i++)
        for (int j = 0; j < NB_COLONNES; j++)
            if (bind_table[i][j] && bind_table[i][j]->cell == cell)
                return bind_table[i][j];
    return NULL;
}

s_bind *bindLookupByPos(int col, int lig)
{
    if (lig < 0 || lig >= NB_LIGNES) return NULL;
    if (col < 0 || col >= NB_COLONNES) return NULL;
    return bind_table[lig][col];
}

void on_cell_edited(GtkEditable *editable, gpointer user_data)
{
    s_bind *b = (s_bind*)user_data;

    const char *text = gtk_entry_get_text(GTK_ENTRY(editable));

    strcpy(b->cell->contenu, text);

    analyser_chaine(b->cell);
    evaluer_sous_graphe(b->cell);

    char buffer[32];
    sprintf(buffer, "%.3f", b->cell->val);

    gtk_entry_set_text(GTK_ENTRY(editable), buffer);
}

gboolean on_cell_focus_out(GtkWidget *widget, GdkEventFocus *event, gpointer user_data)
{
    s_bind *b = (s_bind*)user_data;
    const char *text = gtk_entry_get_text(GTK_ENTRY(widget));
    
    if (text == NULL || text[0] == '\0' || (text[0] == ' ' && text[1] == '\0')) {
        return FALSE;
    }
    
    strcpy(b->cell->contenu, text);
    analyser_chaine(b->cell);
    evaluer_sous_graphe(b->cell);
    
    char buffer[32];
    sprintf(buffer, "%.3f", b->cell->val);
    gtk_entry_set_text(GTK_ENTRY(widget), buffer);
    
    return FALSE;
}

void gui_init()
{
    builder = gtk_builder_new_from_file("monoplan.glade");

    fenetre = GTK_WIDGET(gtk_builder_get_object(builder, "main_window"));
    grille  = GTK_WIDGET(gtk_builder_get_object(builder, "grid_cells"));

    g_signal_connect(fenetre, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    for (int l = 0; l <= NB_LIGNES; l++)
    {
        for (int c = 0; c <= NB_COLONNES; c++)
        {
            if (l == 0 && c == 0) {
                GtkWidget *label = gtk_label_new("");
                gtk_grid_attach(GTK_GRID(grille), label, c, l, 1, 1);
            }
            else if (l == 0) {
                char col_name[2] = {'A' + (c-1), '\0'};
                GtkWidget *label = gtk_label_new(col_name);
                gtk_grid_attach(GTK_GRID(grille), label, c, l, 1, 1);
            }
            else if (c == 0) {
                char row_name[4];
                sprintf(row_name, "%d", l);
                GtkWidget *label = gtk_label_new(row_name);
                gtk_grid_attach(GTK_GRID(grille), label, c, l, 1, 1);
            }
            else {
                GtkWidget *entry = gtk_entry_new();
                gtk_grid_attach(GTK_GRID(grille), entry, c, l, 1, 1);

                s_cell *cell = ajouter_cellule(l-1, c-1);
                bind_create(l-1, c-1, entry, cell);

                g_signal_connect(entry, "focus-out-event",
                    G_CALLBACK(on_cell_focus_out), bind_table[l-1][c-1]);
            }
        }
        gtk_widget_show_all(fenetre);
    }
}
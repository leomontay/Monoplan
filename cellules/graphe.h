#ifndef GRAPHE_CELLULES_H
#define GRAPHE_CELLULES_H

#include "../cellules/cellules.h"

extern s_cell *tableau_cellules[100];
extern int nb_cellules;


void ajouter_successeur(s_cell *src, s_cell *dest);

void calculer_degres_negatifs(s_cell *s_init);

void evaluer_sous_graphe(s_cell *s_init);

void reset_marque_et_degre(s_cell *c);

#endif

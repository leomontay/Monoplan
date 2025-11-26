#ifndef GRAPHE_CELLULES_H
#define GRAPHE_CELLULES_H

#include "../cellules/cellules.h"


void ajouter_successeur(s_cell *src, s_cell *dest);

void calculer_degres_negatifs(s_cell *s_init);

void evaluer_sous_graphe(s_cell *s_init);

#endif

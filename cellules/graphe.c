#include <stdio.h>
#include "../stack/stack.h"
#include "../cellules/cellules.h"
#include "graphe.h"

#define MAX_LISTE 50


void ajouter_successeur(s_cell *src, s_cell *dest)
{
    int i;

    if (src == NULL || dest == NULL)
        return;

    for (i = 0; i < src->nb_successeurs; i++) {
        if (src->successeurs[i] == dest)
            return;
    }

    if (src->nb_successeurs < MAX_SUCC) {
        src->successeurs[src->nb_successeurs] = dest;
        src->nb_successeurs++;
    } else {
        fprintf(stderr, "Trop de successeurs pour la cellule %s\n", src->nom);
    }
}

static void calculer_degres_rec(s_cell *c)
{
    int i;

    if (c == NULL)
        return;

    if (c->marque)
        return;

    c->marque = 1;

    for (i = 0; i < c->nb_successeurs; i++) {
        s_cell *succ = c->successeurs[i];

        if (succ != NULL) {
            succ->degre_neg++;
            calculer_degres_rec(succ);
        }
    }
}

void calculer_degres_negatifs(s_cell *s_init)
{
    calculer_degres_rec(s_init);
}


void evaluer_sous_graphe(s_cell *s_init)
{
    my_stack_t *liste;
    s_cell *courant;
    int i;

    if (s_init == NULL)
        return;

    calculer_degres_negatifs(s_init);

    liste = STACK_CREATE(MAX_LISTE, s_cell *);
    if (liste == NULL) {
        fprintf(stderr, "Erreur\n");
        return;
    }


    if (liste->free < liste->nbMaxElement) {
        ((s_cell **)(liste->value))[liste->free++] = s_init;
    }

    while (!STACK_EMPTY(liste)) {

        courant = ((s_cell **)(liste->value))[--liste->free];

        evaluer_cellule(courant);

        for (i = 0; i < courant->nb_successeurs; i++) {
            s_cell *succ = courant->successeurs[i];

            if (succ != NULL) {
                succ->degre_neg--;

                if (succ->degre_neg == 0) {
                    
                    if (liste->free < liste->nbMaxElement) {
                        ((s_cell **)(liste->value))[liste->free++] = succ;
                    }
                }
            }
        }
    }

    STACK_REMOVE(liste);
}


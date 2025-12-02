#include <stdio.h>
#include "../stack/stack.h"
#include "../cellules/cellules.h"
#include "graphe.h"

#define MAX_LISTE 50


void ajouter_successeur(s_cell *src, s_cell *dest_suc)
{
    int i;

    if (src == NULL || dest_suc == NULL)
        return;

    for (i = 0; i < src->nb_successeurs; i++) {
        if (src->successeurs[i] == dest_suc)
            return;
    }

    if (src->nb_successeurs < MAX_SUCC) {
        src->successeurs[src->nb_successeurs] = dest_suc; //ajoute dest_suc à la fin de la liste des successeurs
        src->nb_successeurs++;
    }
}

void calculer_degre_negatif(s_cell *c) //nb_suseseur_recursive
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
            calculer_degre_negatif(succ);
        }
    }
}


void reset_marque_et_degre(s_cell *c)
{
    if (!c || c->marque == 2) return;

    c->marque = 2;
    c->degre_neg = 0;

    for (int i = 0; i < c->nb_successeurs; i++)
        reset_marque_et_degre(c->successeurs[i]);

    c->marque = 0;    
}


void evaluer_sous_graphe(s_cell *s_init)
{
    if (!s_init) return;

    reset_marque_et_degre(s_init);
    calculer_degre_negatif(s_init);


    s_cell *queue[100];
    int q_start = 0, q_end = 0;
    queue[q_end++] = s_init;


    while (q_start < q_end)
    {
        s_cell *c = queue[q_start++];

        evaluer_cellule(c);

        for (int i = 0; i < c->nb_successeurs; i++)
        {
            s_cell *s = c->successeurs[i];
            s->degre_neg--;

            if (s->degre_neg == 0)
                queue[q_end++] = s;
        }
    }
}


#include <stdio.h>
#include <string.h>
#include "cellules.h"
#include "formule.h"
#include "../stack/stack.h"

double evaluer_cellule(s_cell *cellule)
{
    my_stack_t *pile;
    double resultat = 0.0;
    int i;

    if (cellule == NULL || cellule->nbTokens <= 0) 
    {
        return 0.0;
    }

    pile = STACK_CREATE(cellule->nbTokens, double);
    
    if (pile == NULL) 
    {
        fprintf(stderr, "Ereur\n");
        return 0.0;
    }

    for (i = 0; i < cellule->nbTokens; i++) 
    {
        s_token *jeton = &cellule->tokens[i];

        if (jeton->type == VALUE) 
        {
            STACK_PUSH(pile, jeton->value.cst, double);
        }
        else if (jeton->type == REF)
        {
            double valeur_ref = 0.0;

            extern s_cell *tableau_cellules[];
            extern int nb_cellules;

            for (int j = 0; j < nb_cellules; j++)
            {
                if (strcmp(tableau_cellules[j]->nom, jeton->value.ref) == 0)
                {
                    valeur_ref = evaluer_cellule(tableau_cellules[j]);
                    break;
                }
            }

            STACK_PUSH(pile, valeur_ref, double);
        }
        else if (jeton->type == OPERATOR) 
        {
            if (jeton->value.operator != NULL) {

                // Vérifier 2 valeurs sur la pile
                if (pile->free < 2) {
                    fprintf(stderr, "\n");
                    cellule->val = 0.0;
                    STACK_REMOVE(pile);
                    return 0.0;
                }


                double op1 = STACK_POP(pile, double);
                double op2 = STACK_POP(pile, double);

                STACK_PUSH(pile, op1, double);
                STACK_PUSH(pile, op2, double);

                
                jeton->value.operator(pile);
            }
        }
        else{}
    }

    resultat = STACK_POP(pile, double);
    cellule->val = resultat;
    STACK_REMOVE(pile);
    return resultat;
}

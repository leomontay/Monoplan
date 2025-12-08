#include "cellules.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "../stack/stack.h"

s_cell *tableau_cellules[200];
int nb_cellules = 0;

s_operateur operateurs[] = {
    {'+', op_add},
    {'-', op_sustr},
    {'*', op_mul},
    {'/', op_div},
    {'\0', NULL}
};

void op_add(my_stack_t *eval) {
    double a;
    double b;
    STACK_POP2(eval, a, double);
    STACK_POP2(eval, b, double);
    STACK_PUSH(eval, a + b, double);
}

void op_sustr(my_stack_t *eval) {
    double a;
    double b;
    STACK_POP2(eval, a, double);
    STACK_POP2(eval, b, double);
    STACK_PUSH(eval, b - a, double);
}

void op_mul(my_stack_t *eval) {
    double a;
    double b;   
    STACK_POP2(eval, a, double);
    STACK_POP2(eval, b, double);
    STACK_PUSH(eval, a * b, double);
}

void op_div(my_stack_t *eval) {
    double a;
    double b;   
    STACK_POP2(eval, a, double);
    STACK_POP2(eval, b, double);
    if (a == 0) {
        printf("Erreur : division par zéro.\n");
        STACK_PUSH(eval, 0.0, double);
        return;
    }
    STACK_PUSH(eval, b / a, double);
}

void analyser_chaine(s_cell *c) {
    c->nbTokens = 0;
    char *s = c->contenu;

    if (s[0] == '\0') {
        return;
    }
    if (s[0] != '=') {
        printf("Erreur : la formule doit commencer par '='\n");
        return;
    }
    s++;

    int i = 0;
    while (s[i] != '\0') {
        if (s[i] == ' ') { // ignore les espaces
            i++;
        }
        else if (isdigit(s[i])) { // pour les nombres
            double valeur = atof(&s[i]);
            c->tokens[c->nbTokens].type = VALUE;
            c->tokens[c->nbTokens].value.cst = valeur;
            c->nbTokens++;
            while (isdigit(s[i]) || s[i] == '.') { // avance jusqu'à la fin du nombre
                i++;
            }
        }
        else if (s[i] == '+' || s[i] == '-' || s[i] == '*' || s[i] == '/') { // pour les opérateurs + - * /
            c->tokens[c->nbTokens].type = OPERATOR;
            c->tokens[c->nbTokens].value.operator = operateurs[s[i] == '+' ? 0 :
                                                        s[i] == '-' ? 1 :
                                                        s[i] == '*' ? 2 :
                                                        s[i] == '/' ? 3 : -1].op_fonction;

            c->nbTokens++;
            i++;
        }
        else if (isalpha(s[i])) { // pour les références de la cellule comme par ex A1, B2
            char buffer[10];
            int pos = 0;
            buffer[pos++] = s[i++]; // les lettres
            while (isdigit(s[i])) { // les chiffres
                buffer[pos++] = s[i++];
            }
            buffer[pos] = '\0';
            c->tokens[c->nbTokens].type = REF;
            strcpy(c->tokens[c->nbTokens].value.ref, buffer);
            c->nbTokens++;
        }
        else { // quand un caractère est inconnu on l'ignore et continue
            i++;
        }
    }
}

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


    for (int i = 0; i < nb_cellules; i++) {
        if (tableau_cellules[i]) {
            tableau_cellules[i]->degre_neg = 0;
        }
    }


    for (int i = 0; i < nb_cellules; i++) {
        s_cell *src = tableau_cellules[i];
        if (!src) continue;

        for (int j = 0; j < src->nb_successeurs; j++) {
            s_cell *dst = src->successeurs[j];
            if (dst) dst->degre_neg++;
        }
    }

    printf("degre %s %d\n", s_init->nom, s_init->degre_neg);

    s_cell *queue[200];
    int q_start = 0, q_end = 0;

    for (int i = 0; i < nb_cellules; i++) {
        if (tableau_cellules[i] && tableau_cellules[i]->degre_neg == 0) {
            queue[q_end++] = tableau_cellules[i];
        }
    }

    while (q_start < q_end) {
        s_cell *c = queue[q_start++];

        evaluer_cellule(c);

        for (int j = 0; j < c->nb_successeurs; j++) {
            s_cell *s = c->successeurs[j];
            if (!s) continue;

            s->degre_neg--;
            if (s->degre_neg == 0)
                queue[q_end++] = s;
        }
    }
}

s_cell *ajouter_cellule(int l, int c)
{
    s_cell *cell = malloc(sizeof(s_cell));

    // nom : A1, B2, C10...
    cell->nom[0] = 'A' + c;
    sprintf(cell->nom + 1, "%d", l + 1);

    cell->contenu[0] = '\0';
    cell->nbTokens = 0;
    cell->val = 0.0;
    cell->nb_successeurs = 0;
    cell->marque = 0;
    cell->degre_neg = 0;

    tableau_cellules[nb_cellules++] = cell;

    return cell;
}
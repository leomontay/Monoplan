#include "cellules.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "../stack/stack.h"

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
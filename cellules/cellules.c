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
    {'\0', NULL} // fin de la liste
};

// ---- Exemple d'opérateurs ----
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
    STACK_PUSH(eval, a - b, double);
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
    STACK_PUSH(eval, a / b, double);
}

void analyser_chaine(s_cell *c) {
    c->nbTokens = 0;
    char *s = c->contenu;

    if (s[0] == '=') { // si il y a un = au début on fait comme si il n'existe pas
        s++;
    }

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
        else if (s[i] == '+' || s[i] == '-' || s[i] == '*' || s[i] == '/') { // pour les opérateurs + - * /
            c->tokens[c->nbTokens].type = OPERATOR;
            c->tokens[c->nbTokens].value.operator = operateurs[s[i] == '+' ? 0 :
                                                        s[i] == '-' ? 1 :
                                                        s[i] == '*' ? 2 :
                                                        s[i] == '/' ? 3 : -1].op_fonction;

            c->nbTokens++;
            i++;
        }
        else { // quand un caractère est inconnu on l'ignore et continue
            i++;
        }
    }
}
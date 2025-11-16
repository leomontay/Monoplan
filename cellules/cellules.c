#include "cellules.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

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
            c->tokens[c->nbTokens].value.op = s[i];
            c->nbTokens++;
            i++;
        }
        else { // quand un caractère est inconnu on l'ignore et continue
            i++;
        }
    }
}
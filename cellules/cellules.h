#include "../stack/stack.h"

#ifndef CELLULES_H
#define CELLULES_H

typedef struct token {
    enum { VALUE, REF, OPERATOR } type;
    union {
        double cst;          
        char ref[10];       
        void (*operator) (my_stack_t * eval);            
    } value;
} s_token;

typedef struct cell {
    char contenu[50];   
    double val;     
    s_token tokens[20];     
    int nbTokens;     
} s_cell;

void analyser_chaine(s_cell *c);

#endif
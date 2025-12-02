#ifndef CELLULES_H
#define CELLULES_H

#include "../stack/stack.h"

#define MAX_SUCC 10

typedef struct token {
    enum { VALUE, REF, OPERATOR } type;
    union {
        double cst;    
        char ref[10];  
        void (*operator) (my_stack_t * eval);            
    } value;
} s_token;

typedef struct cell {
    char nom[8];   
    char contenu[50];   
    double val;     
    s_token tokens[20];     
    int nbTokens;
    
    struct cell *successeurs[MAX_SUCC];
    int nb_successeurs;                 
    int degre_neg;                  
    int marque;        

} s_cell;

extern s_cell *tableau_cellules[100];
extern int nb_cellules;


typedef struct operateur {
    char operateur;
    void (*op_fonction) (my_stack_t * eval);    
} s_operateur;

extern s_operateur operateurs[];

void analyser_chaine(s_cell *c);
double evaluer_cellule(s_cell *cellule);
void op_add(my_stack_t *eval);
void op_sustr(my_stack_t *eval);
void op_mul(my_stack_t *eval);
void op_div(my_stack_t *eval);

#endif
#ifndef CELLULES_H
#define CELLULES_H

#include <gtk/gtk.h>
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
    char nom[12];
    char contenu[50];
    double val;
    s_token tokens[20];
    int nbTokens;

    struct cell *successeurs[MAX_SUCC];
    int nb_successeurs;
    int degre_neg;
    int marque;      

} s_cell;

extern s_cell *tableau_cellules[200];
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

void ajouter_successeur(s_cell *src, s_cell *dest);
void calculer_degre_negatif(s_cell *c);
void evaluer_sous_graphe(s_cell *s_init);
void reset_marque_et_degre(s_cell *c);

s_cell *ajouter_cellule(int l, int c);

#endif
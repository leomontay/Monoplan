#include "cellules.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "../stack/stack.h"



int main(void) {
    s_cell c = {0};
    
    // valeur simple
    printf("TEST 1 : valeur simple =42\n");
    strcpy(c.nom, "A1");
    strcpy(c.contenu, "=42");
    analyser_chaine(&c);
    printf("Resultat: %.2f (attendu 42)\n\n", evaluer_cellule(&c));
    
    // operateur +
    printf("TEST 2 : addition =5 3 +\n");
    strcpy(c.contenu, "=5 3 +");
    analyser_chaine(&c);
    printf("Resultat: %.2f (attendu 8)\n\n", evaluer_cellule(&c));
    
    // operateur -
    printf("TEST 3 : soustraction =10 4 -\n");
    strcpy(c.contenu, "=10 4 -");
    analyser_chaine(&c);
    printf("Resultat: %.2f (attendu 6)\n\n", evaluer_cellule(&c));
    
    // operateur *
    printf("TEST 4 : multiplication =6 7 *\n");
    strcpy(c.contenu, "=6 7 *");
    analyser_chaine(&c);
    printf("Resultat: %.2f (attendu 42)\n\n", evaluer_cellule(&c));
    
    // operateur /
    printf("TEST 5 : division =20 4 /\n");
    strcpy(c.contenu, "=20 4 /");
    analyser_chaine(&c);
    printf("Resultat: %.2f (attendu 5)\n\n", evaluer_cellule(&c));
    
    // operation complexe
    printf("TEST 6 : complexe =2 3 + 4 *\n");
    strcpy(c.contenu, "=2 3 + 4 *");
    analyser_chaine(&c);
    printf("Resultat: %.2f (attendu 20)\n\n", evaluer_cellule(&c));
    
    // REF vers 3 cellules
    printf("TEST 7 : references A1 B1 C1\n");
    
    s_cell c1 = {0};
    strcpy(c1.nom, "A1");
    strcpy(c1.contenu, "=10");
    analyser_chaine(&c1);
    
    s_cell c2 = {0};
    strcpy(c2.nom, "B1");
    strcpy(c2.contenu, "=20");
    analyser_chaine(&c2);
    
    s_cell c3 = {0};
    strcpy(c3.nom, "C1");
    strcpy(c3.contenu, "=5");
    analyser_chaine(&c3);
    
    tableau_cellules[0] = &c1;
    tableau_cellules[1] = &c2;
    tableau_cellules[2] = &c3;
    nb_cellules = 3;
    
    s_cell c4 = {0};
    strcpy(c4.nom, "D1");
    strcpy(c4.contenu, "=A1 B1 + C1 *");
    analyser_chaine(&c4);
    printf("Formule: =A1 B1 + C1 *\n");
    printf("Resultat: %.2f (attendu 150)\n\n", evaluer_cellule(&c4));
    
    // cellule vide
    printf("TEST 8 : cellule vide\n");
    s_cell c_vide = {0};
    strcpy(c_vide.nom, "E1");
    strcpy(c_vide.contenu, "");
    analyser_chaine(&c_vide);
    printf("Resultat: %.2f (attendu 0)\n\n", evaluer_cellule(&c_vide));
    
    // juste la valeur 15
    printf("TEST 9 : valeur seule =15\n");
    s_cell c_val = {0};
    strcpy(c_val.nom, "F1");
    strcpy(c_val.contenu, "=15");
    analyser_chaine(&c_val);
    printf("Resultat: %.2f (attendu 15)\n\n", evaluer_cellule(&c_val));
    
    // cas faux
    printf("TEST 10 : cas erreur 10 15 -\n");
    s_cell c_err = {0};
    strcpy(c_err.nom, "G1");
    strcpy(c_err.contenu, "10 15 -");
    analyser_chaine(&c_err);
    printf("Resultat: %.2f (ERREUR attendue)\n", evaluer_cellule(&c_err));
}
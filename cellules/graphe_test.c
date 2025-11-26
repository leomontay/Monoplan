#include <stdio.h>
#include <string.h>
#include "../cellules/cellules.h"
#include "graphe.h"

s_cell *tableau_cellules[10];
int nb_cellules = 0;

int main(void)
{

    s_cell d2 = {0};
    s_cell d3 = {0};
    s_cell a4 = {0};
    s_cell a5 = {0};
    s_cell c5 = {0};


    strcpy(d2.nom, "D2");
    strcpy(d3.nom, "D3");
    strcpy(a4.nom, "A4");
    strcpy(a5.nom, "A5");
    strcpy(c5.nom, "C5");


    strcpy(d2.contenu, "=2");

    strcpy(d3.contenu, "=3");

    strcpy(a4.contenu, "=D3 10 +");

    strcpy(a5.contenu, "=A4 D3 +");

    strcpy(c5.contenu, "=D2 A5 +");

    analyser_chaine(&d2);
    analyser_chaine(&d3);
    analyser_chaine(&a4);
    analyser_chaine(&a5);
    analyser_chaine(&c5);

    tableau_cellules[0] = &d2;
    tableau_cellules[1] = &d3;
    tableau_cellules[2] = &a4;
    tableau_cellules[3] = &a5;
    tableau_cellules[4] = &c5;
    nb_cellules = 5;


    ajouter_successeur(&d3, &a4);
    ajouter_successeur(&d3, &a5);
    ajouter_successeur(&a4, &a5);
    ajouter_successeur(&d2, &c5);
    ajouter_successeur(&a5, &c5);

    printf("=== Evaluation initiale du graphe à partir de D2 ===\n");
    evaluer_sous_graphe(&d2);
    printf("D2 = %.2f\n", d2.val);
    printf("C5 = %.2f\n\n", c5.val);

    d2.marque = d3.marque = a4.marque = a5.marque = c5.marque = 0;
    d2.degre_neg = d3.degre_neg = a4.degre_neg = a5.degre_neg = c5.degre_neg = 0;

    printf("=== Evaluation du sous-graphe à partir de D3 ===\n");
    evaluer_sous_graphe(&d3);
    printf("D3 = %.2f\n", d3.val);
    printf("A4 = %.2f\n", a4.val);
    printf("A5 = %.2f\n", a5.val);
    printf("C5 = %.2f\n", c5.val);


}

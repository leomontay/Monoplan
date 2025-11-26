#include <stdio.h>
#include <string.h>
#include "../cellules/cellules.h"
#include "graphe.h"

s_cell *tableau_cellules[100];
int nb_cellules = 0;

int main(void)
{
    s_cell A1 = {0}, A2 = {0}, A3 = {0};
    s_cell B1 = {0}, B2 = {0}, B3 = {0};

    strcpy(A1.nom, "A1"); strcpy(A2.nom, "A2"); strcpy(A3.nom, "A3");
    strcpy(B1.nom, "B1"); strcpy(B2.nom, "B2"); strcpy(B3.nom, "B3");

    strcpy(A1.contenu, "=2");
    strcpy(A2.contenu, "=3");
    strcpy(A3.contenu, "=A1 A2 +");
    strcpy(B1.contenu, "=A3 1 +");
    strcpy(B2.contenu, "=B1 1 +");
    strcpy(B3.contenu, "=B2 1 +");

    analyser_chaine(&A1);
    analyser_chaine(&A2);
    analyser_chaine(&A3);
    analyser_chaine(&B1);
    analyser_chaine(&B2);
    analyser_chaine(&B3);

  
    ajouter_successeur(&A1, &A3);
    ajouter_successeur(&A2, &A3);
    ajouter_successeur(&A3, &B1);
    ajouter_successeur(&B1, &B2);
    ajouter_successeur(&B2, &B3);

    tableau_cellules[0] = &A1;
    tableau_cellules[1] = &A2;
    tableau_cellules[2] = &A3;
    tableau_cellules[3] = &B1;
    tableau_cellules[4] = &B2;
    tableau_cellules[5] = &B3;
    nb_cellules = 6;


    
    evaluer_cellule(&A1);
    evaluer_cellule(&A2);
    evaluer_sous_graphe(&A1); 

    printf("Initial : A1=%.0f A2=%.0f A3=%.0f  B1=%.0f B2=%.0f B3=%.0f\n",
           A1.val, A2.val, A3.val, B1.val, B2.val, B3.val);

   
    strcpy(A1.contenu, "=5");
    analyser_chaine(&A1);
    evaluer_sous_graphe(&A1); 

    printf("A1=5  : A1=%.0f A2=%.0f A3=%.0f  B1=%.0f B2=%.0f B3=%.0f\n",
           A1.val, A2.val, A3.val, B1.val, B2.val, B3.val);

   
    strcpy(A2.contenu, "=10");
    analyser_chaine(&A2);
    evaluer_sous_graphe(&A2); 
    printf("A2=10 : A1=%.0f A2=%.0f A3=%.0f  B1=%.0f B2=%.0f B3=%.0f\n",
           A1.val, A2.val, A3.val, B1.val, B2.val, B3.val);

}

#include <stdio.h>
#include <string.h>
#include "../cellules/cellules.h"
#include "graphe.h"

s_cell *tableau_cellules[100];
int nb_cellules = 0;

int main(void)
{
     s_cell A1 = (s_cell){0};
    s_cell B1 = (s_cell){0};
    s_cell C1 = (s_cell){0}, C2 = (s_cell){0};
    s_cell E1 = (s_cell){0}, E2 = (s_cell){0}, E3 = (s_cell){0}, E4 = (s_cell){0}, E5 = (s_cell){0};

    // 1) TEST FAUX : A1 
    strcpy(A1.nom, "A1");
    strcpy(A1.contenu, "A1 +");
    analyser_chaine(&A1);

    // 2) TEST SIMPLE : B1 = 2
    strcpy(B1.nom, "B1");
    strcpy(B1.contenu, "=2");
    analyser_chaine(&B1);

    // 3) TEST : C2 = C1 * 10
    strcpy(C1.nom, "C1");
    strcpy(C1.contenu, "=2");

    strcpy(C2.nom, "C2");
    strcpy(C2.contenu, "=C1 10 *");

    analyser_chaine(&C1);
    analyser_chaine(&C2);
    ajouter_successeur(&C1, &C2);

    // 4) TEST : E5 = E1 + E2 + E3 + E4
    strcpy(E1.nom, "E1");
    strcpy(E2.nom, "E2");
    strcpy(E3.nom, "E3");
    strcpy(E4.nom, "E4");
    strcpy(E5.nom, "E5");

    strcpy(E1.contenu, "=E2 2 +");
    strcpy(E2.contenu, "=5");
    strcpy(E3.contenu, "=5");
    strcpy(E4.contenu, "=5");
    strcpy(E5.contenu, "=E1 E3 + E4 +");

    analyser_chaine(&E1);
    analyser_chaine(&E2);
    analyser_chaine(&E3);
    analyser_chaine(&E4);
    analyser_chaine(&E5);

    // Dépendances
    ajouter_successeur(&E1, &E5);
    ajouter_successeur(&E2, &E1);
    ajouter_successeur(&E2, &E5);
    ajouter_successeur(&E3, &E5);
    ajouter_successeur(&E4, &E5);

    // Ajout au tableau global
    tableau_cellules[0] = &A1;
    tableau_cellules[1] = &B1;
    tableau_cellules[2] = &C1;
    tableau_cellules[3] = &C2;
    tableau_cellules[4] = &E1;
    tableau_cellules[5] = &E2;
    tableau_cellules[6] = &E3;
    tableau_cellules[7] = &E4;
    tableau_cellules[8] = &E5;
    nb_cellules = 9;

    // Affichages
    printf("TEST 1 (FAUX) : A1 contenu=\"A1 +\"\n");
    printf("Resultat A1 = %.2f (attendu 0)\n\n", evaluer_cellule(&A1));

    printf("TEST 2 : B1 = 2\n");
    printf("B1 = %.0f (attendu 2)\n\n", evaluer_cellule(&B1));

    printf("TEST 3 : C2 = C1 * 10\n");
    evaluer_sous_graphe(&C1);
    printf("C1=%.0f  C2=%.0f (attendu 20)\n\n", C1.val, C2.val);

    printf("TEST 4 : E5 = E1 + E2 + E3 + E4\n");
    evaluer_sous_graphe(&E5);
    printf("E1=%.0f E2=%.0f E3=%.0f E4=%.0f E5=%.0f (attendu 17)\n",
           E1.val, E2.val, E3.val, E4.val, E5.val);
}

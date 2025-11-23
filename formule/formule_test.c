#include <stdio.h>
#include <string.h>
#include "cellules.h"
#include "formule.h"

s_cell *tableau_cellules[3];
int nb_cellules = 3;

int main(void)
{
   // Tests avec chacun des opérateurs + complexes + simples
   s_cell t_ops = (s_cell){0};


   t_ops.tokens[0].type = VALUE;
   t_ops.tokens[0].value.cst = 8.0;     

   t_ops.tokens[1].type = VALUE;
   t_ops.tokens[1].value.cst = 4.0;

   t_ops.tokens[2].type = OPERATOR;
   t_ops.tokens[2].value.operator = op_div;

   t_ops.tokens[3].type = VALUE;
   t_ops.tokens[3].value.cst = 3.0;

   t_ops.tokens[4].type = OPERATOR;
   t_ops.tokens[4].value.operator = op_add;

   t_ops.tokens[5].type = VALUE;
   t_ops.tokens[5].value.cst = 5.0;

   t_ops.tokens[6].type = OPERATOR;
   t_ops.tokens[6].value.operator = op_mul;

   t_ops.tokens[7].type = VALUE;
   t_ops.tokens[7].value.cst = 10.0;

   t_ops.tokens[8].type = OPERATOR;
   t_ops.tokens[8].value.operator = op_sustr;

   t_ops.nbTokens = 9;

   printf("Tests avec tout opérateurs + complexes + simples ((((8/4)+3)*5)-10) : %f (attendu 15)\n",evaluer_cellule(&t_ops));


// Calcul entre cellules : A = 10 et B = 5, C = A + B
   s_cell cellA = (s_cell){0};
   strcpy(cellA.nom, "A"); 
   cellA.tokens[0].type = VALUE;
   cellA.tokens[0].value.cst = 10.0;
   cellA.nbTokens = 1;

   s_cell cellB = (s_cell){0};
   strcpy(cellB.nom, "B");
   cellB.tokens[0].type = VALUE;
   cellB.tokens[0].value.cst = 5.0;
   cellB.nbTokens = 1;


   s_cell cellC = (s_cell){0};
   strcpy(cellC.nom, "C");

   cellC.tokens[0].type = REF;
   strcpy(cellC.tokens[0].value.ref, "A");

   cellC.tokens[1].type = REF;
   strcpy(cellC.tokens[1].value.ref, "B");

   cellC.tokens[2].type = OPERATOR;
   cellC.tokens[2].value.operator = op_add;

   cellC.nbTokens = 3;

   strcpy(cellA.nom, "A");
   strcpy(cellB.nom, "B");
   strcpy(cellC.nom, "C");

   tableau_cellules[0] = &cellA;
   tableau_cellules[1] = &cellB;
   tableau_cellules[2] = &cellC;

   printf("Test (A + B) %f (attendu 15)\n",evaluer_cellule(&cellC));



   // Cas où il n'y a rien
   s_cell cell_vide = (s_cell){0};
   cell_vide.nbTokens = 0;  
   printf("cellule vide : %f (attendu 0)\n",evaluer_cellule(&cell_vide));


   // Cas valeur seule 42
   s_cell cell_val = (s_cell){0};

   cell_val.tokens[0].type = VALUE;
   cell_val.tokens[0].value.cst = 42.0;
   cell_val.nbTokens = 1;

   printf("valeur seule 42 : %f (attendu 42)\n",evaluer_cellule(&cell_val));

  
   // Cas erreur (opérateur avec un seul opérande)
   s_cell cell_err = (s_cell){0};

   cell_err.tokens[0].type = VALUE;
   cell_err.tokens[0].value.cst = 10.0;

   cell_err.tokens[1].type = OPERATOR;
   cell_err.tokens[1].value.operator = op_sustr; 

   cell_err.nbTokens = 2;

   printf("%fCas erreur ATTENDU ERREUR\n",evaluer_cellule(&cell_err));

}

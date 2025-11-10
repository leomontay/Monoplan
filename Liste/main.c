#include "liste.h"
#include <stdio.h>
#include <stdlib.h>

int main(void) {

    node_t *liste = list_create();

    int a = 1, b = 2, c = 3, d = 4, nouveau = 42;

    liste = list_insert(liste, &a);
    liste = list_insert(liste, &b);
    liste = list_insert(liste, &c);

    printf("Tête : %d\n", *(int *)list_get_data(liste));

    printf("\n4 ajouté à la fin\n");
    liste = list_append(liste, &d);

    node_t *last = liste;
    while (last->next) 
        last = last->next;
    printf("Dernier  : %d\n", *(int *)list_get_data(last));

    printf("\nSuppression de 2\n");
    liste = list_remove(liste, &b);

    printf("\nSuppression de la tête\n");
    int ancienne_tete = *(int *)list_get_data(liste);

    liste = list_headRemove(liste);

    if (liste)
        printf("Nouvelle tête : %d (ancienne : %d)\n", *(int *)list_get_data(liste), ancienne_tete);
    else
        printf("Liste vide.\n"); 
    printf("\nModification tete = 42\n");
    list_set_data(liste, &nouveau);

    printf("Nouveau chiffre de la tête : %d\n", *(int *)list_get_data(liste));

    list_destroy(liste);
}
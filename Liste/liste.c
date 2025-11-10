#include "liste.h"
#include <stdio.h>
#include <stdlib.h>

node_t * list_create(void) {
    node_t* liste = (node_t*)malloc(sizeof(node_t));
    if (liste == NULL) {
        fprintf(stderr, "Erreur d'allocation mémoire\n");
        exit(EXIT_FAILURE);
    }
    liste->next = NULL;
    return liste;
}

void * list_get_data(const node_t * node) {
    if (!node) return NULL;
    return node->data;
}

void list_set_data(node_t * node, void * data) {
    if (node) {
        node->data = data;
    }
}

node_t * list_next(node_t * node) {
    if (!node) return NULL;
    return node->next;
}

node_t * list_insert(node_t * head, void * data) {
    node_t* new_node = (node_t*)malloc(sizeof(node_t));
    if (new_node == NULL) {
        fprintf(stderr, "Erreur d'allocation mémoire\n");
        exit(EXIT_FAILURE);
    }
    new_node->data = data;
    new_node->next = head;
    return new_node;
}

node_t * list_append(node_t * head, void * data) {
        
}

node_t * list_remove(node_t * head, void * data){

}

node_t * list_headRemove(node_t * head) {

}

void list_destroy(node_t * head){

}
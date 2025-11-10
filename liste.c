#include "liste.h"
#include <stdio.h>
#include <stdlib.h>

node_t * list_create(void) {
    return NULL;
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
    node_t *new_node = (node_t*)malloc(sizeof(node_t));
    if (!new_node) {
        fprintf(stderr, "Ereur\n");
        exit(EXIT_FAILURE);
    }
    new_node->data = data;
    new_node->next = NULL;

    if (!head) return new_node;

    node_t *cur = head;
    while (cur->next) cur = cur->next;
    cur->next = new_node;
    return head;
}

node_t * list_remove(node_t * head, void * data){
 if (!head) return NULL;

    if (head->data == data) {
        node_t *next = head->next;
        free(head);
        return next;
    }

    node_t *prev = head;
    node_t *cur = head->next;
    while (cur) {
        if (cur->data == data) {
            prev->next = cur->next;
            free(cur);
            break;
        }
        prev = cur;
        cur = cur->next;
    }
    return head;
}

node_t * list_headRemove(node_t * head) {
 if (!head) return NULL;
    node_t *next = head->next;
    free(head);
    return next;
}

void list_destroy(node_t * head){
  node_t *cur = head;
    while (cur) {
        node_t *next = cur->next;
        free(cur);
        cur = next;
    }
}
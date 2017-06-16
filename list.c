//
// Created by red on 6/10/17.
//

#include "list.h"

void _list_init(linked_list* list) {
    struct node* head = calloc(sizeof(struct node), 1);
    head->value = NULL;
    head->next = NULL;
    list->head = head;
    list->tail = head;
    list->size = 0;
}

void _list_free(linked_list* list) {

}

void _list_append(linked_list* list, void* value) {
    struct node* list_node = calloc(sizeof(struct node), 1);
    list_node->next = NULL;
    list_node->value = value;
    list->tail = list_node;
    struct node* n = list->head;
    while(n->next != NULL) {
        n = n->next;
    }
    n->next = list_node;
}

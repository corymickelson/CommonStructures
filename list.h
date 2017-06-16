//
// Created by red on 6/10/17.
//

#ifndef STRUCTURES_LIST_H
#define STRUCTURES_LIST_H

#include <stdlib.h>
#include <stdbool.h>

#define list_init(li) linked_list li; _list_init(&li)
#define list_free(li) _list_free(&li)
#define list_append(li, val) _list_append(&li, (void*) val)

struct node {
    void *value;
    struct node *next;
};

typedef struct {
    struct node *head;
    struct node *tail;
    int size;
} linked_list;

void _list_init(linked_list *);

void _list_append(linked_list *, void *);

void _list_free(linked_list*);

#endif //STRUCTURES_LIST_H

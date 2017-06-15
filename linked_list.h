//
// Created by skyslope on 6/13/17.
//

#ifndef STRUCTURES_LINKED_LIST_H
#define STRUCTURES_LINKED_LIST_H

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

#define llist_init(list) linked_list list; _llist_init(&list)
#define llist_free(list) _llist_free(&list)
#define llist_push(list, value) _llist_push(&list, (void*) value)
/**
 * @name llist_pop
 * @def linked list pop of (t)
 */
#define llist_pop(list, t) (t) _llist_pop(&list)
#define llist_shift(list, value) _llist_shift(&list, (void*) value)
/**
 * @name llist_unshift
 * @def linked list unshift of (t)
 */
#define llist_unshift(list, t) (t) _llist_unshift(&list)

struct list_node {
    void *data;
    struct list_node *next;
};

typedef struct {
    struct list_node *head;
    struct list_node *tail;
    int size;
} linked_list;

void _llist_init(linked_list *);

void _llist_free(linked_list *);

void _llist_push(linked_list *, void *);

void _llist_shift(linked_list *, void *);

void* _llist_pop(linked_list *);

void* _llist_unshift(linked_list *);

#endif //STRUCTURES_LINKED_LIST_H

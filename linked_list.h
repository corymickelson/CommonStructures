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
#define llist_get(list, i) _llist_get(&list, i)
#define llist_compare_values(a, b, t) (t) a == (t) b ? true : false
/**
 * @name llist_index_of
 * @details returns first index where item->data == val
 */
#define llist_index_of(list, t, val, result) int result=-1; {\
    struct list_node* i = list.head;\
    int count = 0;\
    while(i->next != NULL) {\
        bool compare = llist_compare_values(i->data, val, t);\
        if(compare == true) {\
            result = count;\
            break;\
        }\
        i = i->next;\
        count++;\
    }\
    if(llist_compare_values(i->data, val, t) == true) result = count;\
    \
}

/**
 * @name llist_index_of_all
 * @details returns index of all matches of i->data == val, results array initialized to size of list.
 */
#define llist_index_of_all(list, t, val, result) {\
    struct list_node* i = list.head;\
    int count = 0;\
    int result_idx = 0;\
    while(i->next != NULL) {\
        bool compare = llist_compare_values(i->data, val, t);\
        if(compare == true) {\
            result[result_idx] = count;\
            result_idx++;\
        }\
        i = i->next;\
        count++;\
    }\
    if(llist_compare_values(i->data, val, t) == true) result[result_idx] = count;\
    \
}

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

void* _llist_get(linked_list*, int);


#endif //STRUCTURES_LINKED_LIST_H

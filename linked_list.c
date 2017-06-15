//
// Created by skyslope on 6/13/17.
//

#include "linked_list.h"

void _llist_init(linked_list *list) {
    struct list_node *head = malloc(sizeof(struct list_node));
    head->data = NULL;
    head->next = NULL;
    list->size = 0;
    list->head = head;
    list->tail = head;
}

void _llist_free(linked_list *list) {
    struct list_node *curr = list->head->next;
    while (curr != NULL) {
        struct list_node *tmp = curr->next;
        free(curr);
        curr = tmp;
    }
    free(curr);
}

/**
 * @def push data to end of list.
 * @param list
 * @param data
 */
void _llist_push(linked_list *list, void *data) {
    if (list->size == 0) {
        list->head->data = data;
        list->size++;
    } else {
        struct list_node *new_node = malloc(sizeof(struct list_node));
        struct list_node *old_tail_node = list->tail;
        new_node->next = NULL;
        new_node->data = data;
        old_tail_node->next = new_node;
        list->tail = new_node;
        list->size++;
    }

}

/**
 * @def push data to head of list.
 * @param list
 * @param data
 */
void _llist_shift(linked_list *list, void *data) {
    if (list->size == 0) {
        list->head->data = data;
        list->size++;
    } else {
        struct list_node *node = malloc(sizeof(struct list_node));
        node->data = data;
        struct list_node *old_head = list->head;
        node->next = old_head;
        list->head = node;
        list->size++;
    }

}

/**
 * @def remove node from end of list
 * @param list
 */
void* _llist_pop(linked_list *list) {
    if(list->size == 0) {
        printf("empty list");
        return NULL;
    }
    struct list_node* item = list->tail;

    struct list_node* i = list->head;
    while(i->next != NULL) {
        struct list_node *next = i->next;
        if(next->next == NULL) {
            i->next = NULL;
            list->tail = i;
        }
        i = next;
    }
    list->size--;
    return item->data;
}

/**
 * @def remove node from head of list.
 *      llist_unshift casts value to (t)
 * @param list
 * @see llist_unshift
 */
void* _llist_unshift(linked_list *list) {
    if(list->size == 0) {
        printf("empty list");
        return NULL;
    }
    if(list->head->data != NULL && list->head->next == NULL) {
        return list->head->data;
    }
    if(list->head->next == NULL && list->head->data == NULL) {
        return NULL;
    }
    struct list_node* item = list->head;
    struct list_node* i = item->next;
    list->head = i;
    list->size--;
    return item->data;
}
